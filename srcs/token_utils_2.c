/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:54:06 by facu              #+#    #+#             */
/*   Updated: 2023/12/02 18:59:14 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_exit_status(char **ptr, char **ret)
{
	char	*expansion;

	expansion = 0;
	expansion = ft_itoa(g_exit_status);
	if (expansion)
	{
		ft_strlcpy(*ret, expansion, ft_strlen(expansion) + 1);
		*ret += ft_strlen(expansion);
		free(expansion);
	}
	(*ptr)++;
}

void	extract_alpha_variable(char **ptr, char **ret, t_shell *shell)
{
	char	*expansion;

	expansion = 0;
	expand_variable(*ptr, &expansion, shell);
	if (expansion)
	{
		ft_strlcpy(*ret, expansion, ft_strlen(expansion) + 1);
		*ret += ft_strlen(expansion);
		free(expansion);
	}
	(*ptr) += ft_strcspn(*ptr, "\" \t\r\n\v");
}

void	handle_question_mark(char **ret)
{
	**ret = '$';
	(*ret)++;
}

void	extract_variable(char **ptr, char **ret, t_shell *shell)
{
	(*ptr)++;
	if (**ptr == '?')
		extract_exit_status(ptr, ret);
	else if (ft_isalpha(**ptr))
		extract_alpha_variable(ptr, ret, shell);
	else
		handle_question_mark(ret);
}

void	extract_single_quotes(char **ptr, char **ret)
{
	(*ptr)++;
	while (**ptr != '\'')
		*(*ret)++ = *(*ptr)++;
	(*ptr)++;
}

void	extract_double_quotes(char **ptr, char **ret, t_shell *shell)
{
	(*ptr)++;
	while (**ptr != '\"')
	{
		if (**ptr == '$')
			extract_variable(ptr, ret, shell);
		else
			*(*ret)++ = *(*ptr)++;
	}
	(*ptr)++;
}

char	*extract_token(char **ptr, int len, t_shell *shell)
{
	char	*ret;
	char	*tmp;

	tmp = ft_calloc(len + 1, sizeof(char));
	ret = tmp;
	while (*ptr)
	{
		if (**ptr == '\'')
			extract_single_quotes(ptr, &tmp);
		else if (**ptr == '\"')
			extract_double_quotes(ptr, &tmp, shell);
		else if (**ptr == '$')
			extract_variable(ptr, &tmp, shell);
		else if (ft_strchr(" \t\r\n\v<|>&;", **ptr))
			break ;
		else
			*tmp++ = *((*ptr)++);
	}
	return (ret);
}
