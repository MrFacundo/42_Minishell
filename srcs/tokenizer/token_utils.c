/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:35:54 by facu              #+#    #+#             */
/*   Updated: 2023/12/19 20:31:06 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion_len(char **cmd_ptr, int *len, t_shell *shell)
{
	char	*expansion;

	expansion = 0;
	(*cmd_ptr)++;
	if (**cmd_ptr == '?')
	{
		expansion = ft_itoa(g_exit_status);
		*len += ft_strlen(expansion);
		(*cmd_ptr)++;
	}
	else if (ft_isalpha(**cmd_ptr))
	{
		expand_variable(*cmd_ptr, &expansion, shell);
		*len += ft_strlen(expansion);
		(*cmd_ptr) += ft_strcspn(*cmd_ptr, "\" \t\r\n\v$");
	}
	else
		(*len)++;
	free(expansion);
}

int	s_quoted_segment_len(char **cmd_ptr, int *len, int *has_quotes)
{
	*has_quotes = 1;
	(*cmd_ptr)++;
	while (**cmd_ptr)
	{
		if (**cmd_ptr == '\'')
		{
			(*cmd_ptr)++;
			if (**cmd_ptr == '\'')
				(*cmd_ptr)++;
			else
				return (0);
		}
		else
		{
			(*len)++;
			(*cmd_ptr)++;
		}
	}
	return (-1);
}

int	d_quoted_segment_len(char **cmd_ptr, t_shell *shell, int *len, int *has_quotes)
{
	*has_quotes = 1;
	(*cmd_ptr)++;
	while (**cmd_ptr)
	{
		if (**cmd_ptr == '$')
		{
			expansion_len(cmd_ptr, len, shell);
		}
		else
		{
			if (**cmd_ptr == '\"')
			{
				(*cmd_ptr)++;
				if (**cmd_ptr == '\"')
					(*cmd_ptr)++;
				else
					return (0);
			}
			else
			{
				(*len)++;
				(*cmd_ptr)++;
			}
		}
	}
	return (-1);
}

int	calculate_token_length(char *cmd_ptr, t_shell *shell, int *has_quotes)
{
	int	len;

	len = 0;
	while (*cmd_ptr)
	{
		if (*cmd_ptr == '\'' && s_quoted_segment_len(&cmd_ptr, &len, has_quotes) == -1)
			return (-1);
		else if (*cmd_ptr == '\"' && d_quoted_segment_len(&cmd_ptr, shell,
				&len, has_quotes) == -1)
			return (-1);
		else if (*cmd_ptr == '$')
			expansion_len(&cmd_ptr, &len, shell);
		else if (ft_strchr(" \t\r\n\v<|>&;", *cmd_ptr))
			break ;
		else
		{
			cmd_ptr++;
			len++;
		}
	}
	return (len);
}
