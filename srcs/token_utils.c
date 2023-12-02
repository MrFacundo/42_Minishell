/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:35:54 by facu              #+#    #+#             */
/*   Updated: 2023/12/02 16:46:29 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expansion_len(char **ptr, int *len, t_shell *shell)
{
	char	*expansion;

	expansion = 0;
	(*ptr)++;
	if (**ptr == '?')
	{
		*len += ft_strlen(expansion = ft_itoa(g_exit_status));
		(*ptr)++;
	}
	else if (ft_isalpha(**ptr))
	{
		expand_variable(*ptr, &expansion, shell);
		*len += ft_strlen(expansion);
		(*ptr) += ft_strcspn(*ptr, "\" \t\r\n\v");
	}
	else
		(*len)++;
	free(expansion);
}

int	s_quoted_segment_len(char **ptr, int *len)
{
	(*ptr)++;
	while (**ptr)
	{
		if (**ptr == '\'')
		{
			(*ptr)++;
			return (0);
		}
		(*len)++;
		(*ptr)++;
	}
	return (-1);
}

int	d_quoted_segment_len(char **ptr, t_shell *shell, int *len)
{
	(*ptr)++;
	while (**ptr)
	{
		if (**ptr == '$')
		{
			expansion_len(ptr, len, shell);
		}
		else
		{
			if (**ptr == '\"')
			{
				(*ptr)++;
				return (0);
			}
			(*len)++;
			(*ptr)++;
		}
	}
	return (-1);
}

int	calculate_token_length(char *ptr, t_shell *shell)
{
	int	len;

	len = 0;
	while (*ptr)
	{
		if (*ptr == '\'' && s_quoted_segment_len(&ptr, &len) == -1)
			return (-1);
		else if (*ptr == '\"' && d_quoted_segment_len(&ptr, shell, &len) == -1)
			return (-1);
		else if (*ptr == '$')
			expansion_len(&ptr, &len, shell);
		else if (ft_strchr(" \t\r\n\v<|>&;", *ptr))
			break ;
		else
		{
			ptr++;
			len++;
		}
	}
	return (len);
}
