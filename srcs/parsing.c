/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/03 15:07:38 by facu             ###   ########.fr       */
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

t_node	*parsepipe(char **cmd_ptr, t_shell *shell)
{
	t_node	*left;

	left = parseexec(cmd_ptr, shell);
	if (shell->parsing_error != TOKEN_ERROR && peek(cmd_ptr, "|"))
	{
		get_token(cmd_ptr, 0, shell);
		if (**cmd_ptr == '\0' || peek(cmd_ptr, "|()&;<>"))
			return handle_parse_error(left, "Parse error near pipe", shell);
		return (pipenode(left, parsepipe(cmd_ptr, shell)));
	}
	return (left);
}

t_node	*parseredirs(t_node *node, char **cmd_ptr, t_shell *shell)
{
	int		token;
	int		file_token;
	char 	*tkn_ptr;

	while (peek(cmd_ptr, "<>"))
	{
		token = get_token(cmd_ptr, 0, shell);
		file_token = get_token(cmd_ptr, &tkn_ptr, shell);
		if (file_token != 'a')
			return handle_parse_error(node, "Parse error near redirection", shell);
		if (token == '<')
			node = redircmd(node, tkn_ptr, O_RDONLY, 0);
		else if (token == '>')
			node = redircmd(node, tkn_ptr, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '+')
			node = redircmd(node, tkn_ptr, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token == '-')
			node = heredoccmd(node, tkn_ptr);
	}
	return (node);
}

t_node	*parseexec(char **cmd_ptr, t_shell *shell)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*tkn_ptr;
	int 		token;

	ret = execnode();
	exec_node = (t_execnode *)ret;
	while (!peek(cmd_ptr, "<>|()&;"))
	{
		token = get_token(cmd_ptr, &tkn_ptr, shell);
		if (token == 0)
			break ;
		else if (token == 'e')
			return handle_parse_error(ret, "Parse error near quotes", shell);
		else if (token == 'a')
			exec_node->av[exec_node->ac++] = tkn_ptr;
		if (exec_node->ac >= MAXARGS - 1)
			return handle_parse_error(ret, "Max arguments exceeded", shell);
		ret = parseredirs(ret, cmd_ptr, shell);
	}
	exec_node->av[exec_node->ac] = 0;
	return (ret);
}