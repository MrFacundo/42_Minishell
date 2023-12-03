/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/03 01:07:29 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*handle_parse_error(t_node *ret, const char *error_message, t_shell *shell)
{
    shell->parsing_error = TOKEN_ERROR;
    print_error(1, error_message);
    return ret;
}

t_node	*parse_cmd(char *cmd, t_shell *shell)
{
	t_node	*node;

	shell->parsing_error = 0;
	node = parsepipe(&cmd, shell);
	if (shell->parsing_error == TOKEN_ERROR)
		g_exit_status = TOKEN_ERROR;
	return (node);
}

t_node	*parsepipe(char **ptr_to_cmd, t_shell *shell)
{
	t_node	*left;

	left = parseexec(ptr_to_cmd, shell);
	if (shell->parsing_error != TOKEN_ERROR && peek(ptr_to_cmd, "|"))
	{
		get_token(ptr_to_cmd, 0, shell);
		if (**ptr_to_cmd == '\0' || peek(ptr_to_cmd, "|()&;<>"))
			return handle_parse_error(left, "Parse error near pipe", shell);
		return (pipenode(left, parsepipe(ptr_to_cmd, shell)));
	}
	return (left);
}

t_node	*parseredirs(t_node *node, char **ptr_to_cmd, t_shell *shell)
{
	int		token;
	int		file_token;
	char 	*ptr_to_token;

	while (peek(ptr_to_cmd, "<>"))
	{
		token = get_token(ptr_to_cmd, 0, shell);
		file_token = get_token(ptr_to_cmd, &ptr_to_token, shell);
		if (file_token != 'a')
			return handle_parse_error(node, "Parse error near redirection", shell);
		if (token == '<')
			node = redircmd(node, ptr_to_token, O_RDONLY, 0);
		else if (token == '>')
			node = redircmd(node, ptr_to_token, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '+')
			node = redircmd(node, ptr_to_token, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token == '-')
			node = heredoccmd(node, ptr_to_token);
	}
	return (node);
}

t_node	*parseexec(char **ptr_to_cmd, t_shell *shell)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*ptr_to_token;
	int 		token;

	ret = execnode();
	exec_node = (t_execnode *)ret;
	while (!peek(ptr_to_cmd, "<>|()&;"))
	{
		token = get_token(ptr_to_cmd, &ptr_to_token, shell);
		if (token == 0)
			break ;
		else if (token == 'e')
			return handle_parse_error(ret, "Parse error near quotes", shell);
		else if (token == 'a')
			exec_node->av[exec_node->ac++] = ptr_to_token;
		if (exec_node->ac >= MAXARGS - 1)
			return handle_parse_error(ret, "Max arguments exceeded", shell);
		ret = parseredirs(ret, ptr_to_cmd, shell);
	}
	exec_node->av[exec_node->ac] = 0;
	return (ret);
}