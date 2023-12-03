/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:54:06 by facu              #+#    #+#             */
/*   Updated: 2023/12/03 15:08:58 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_question_mark(char **ret)
{
	**ret = '$';
	(*ret)++;
}

void	extract_variable(char **cmd_ptr, char **ret, t_shell *shell)
{
	(*cmd_ptr)++;
	if (**cmd_ptr == '?')
		extract_exit_status(cmd_ptr, ret);
	else if (ft_isalpha(**cmd_ptr))
		extract_alpha_variable(cmd_ptr, ret, shell);
	else
		handle_question_mark(ret);
}

void	extract_single_quotes(char **cmd_ptr, char **ret)
{
	(*cmd_ptr)++;
	while (**cmd_ptr != '\'')
		*(*ret)++ = *(*cmd_ptr)++;
	(*cmd_ptr)++;
}

void	extract_double_quotes(char **cmd_ptr, char **ret, t_shell *shell)
{
	(*cmd_ptr)++;
	while (**cmd_ptr != '\"')
	{
		if (**cmd_ptr == '$')
			extract_variable(cmd_ptr, ret, shell);
		else
			*(*ret)++ = *(*cmd_ptr)++;
	}
	(*cmd_ptr)++;
}

char	*extract_token(char **cmd_ptr, int len, t_shell *shell)
{
	char	*ret;
	char	*tmp;

	tmp = ft_calloc(len + 1, sizeof(char));
	ret = tmp;
	while (*cmd_ptr)
	{
		if (**cmd_ptr == '\'')
			extract_single_quotes(cmd_ptr, &tmp);
		else if (**cmd_ptr == '\"')
			extract_double_quotes(cmd_ptr, &tmp, shell);
		else if (**cmd_ptr == '$')
			extract_variable(cmd_ptr, &tmp, shell);
		else if (ft_strchr(" \t\r\n\v<|>&;", **cmd_ptr))
			break ;
		else
			*tmp++ = *((*cmd_ptr)++);
	}
	return (ret);
}
