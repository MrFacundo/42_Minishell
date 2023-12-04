/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/04 03:53:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*handle_parse_error(t_node *ret, const char *error_message,
		t_shell *shell)
{
	shell->parsing_error = TOKEN_ERROR;
	print_error(1, error_message);
	return (ret);
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
			return (handle_parse_error(left, "Parse error near pipe", shell));
		return (pipenode(left, parsepipe(cmd_ptr, shell)));
	}
	return (left);
}

t_node	*reverse_redir_nodes_help(t_node *root)
{
	t_node	*prev;
	t_node	*current;
	t_node	*next;

	prev = 0;
	current = root;
	next = 0;
	while (current->type == REDIR)
	{
		next = ((t_redirnode *)current)->execnode;
		((t_redirnode *)current)->execnode = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

t_node	*reverse_redir_nodes(t_node *node)
{
	t_node	*new_root;
	t_node	*exec_node;

	exec_node = node;
	while (exec_node->type == REDIR)
		exec_node = ((t_redirnode *)exec_node)->execnode;
	new_root = reverse_redir_nodes_help(node);
	((t_redirnode *)node)->execnode = exec_node;
	return (new_root);
}

t_node	*parseredirs(t_node *node, char **cmd_ptr, t_shell *shell)
{
	int		token;
	int		file_token;
	char	*tkn_ptr;

	while (peek(cmd_ptr, "<>"))
	{
		token = get_token(cmd_ptr, 0, shell);
		file_token = get_token(cmd_ptr, &tkn_ptr, shell);
		if (file_token != 'a')
			return (handle_parse_error(node, "Parse error near redirection", shell));
		if (token == '<')
			node = redircmd(node, tkn_ptr, O_RDONLY, 0);
		else if (token == '>')
			node = redircmd(node, tkn_ptr, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '+')
			node = redircmd(node, tkn_ptr, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token == '-')
			node = heredoccmd(node, tkn_ptr);
	}
	if (node->type == REDIR)
		return (reverse_redir_nodes(node));
	return (node);
}

t_node	*parseexec(char **cmd_ptr, t_shell *shell)
{
	t_node *ret;
	t_execnode *exec_node;
	char *tkn_ptr;
	int token;

	ret = execnode();
	exec_node = (t_execnode *)ret;
	while (!peek(cmd_ptr, "<>|()&;"))
	{
		token = get_token(cmd_ptr, &tkn_ptr, shell);
		if (token == 0)
			break ;
		else if (token == 'e')
			return (handle_parse_error(ret, "Parse error near quotes", shell));
		else if (token == 'a')
			exec_node->av[exec_node->ac++] = tkn_ptr;
		if (exec_node->ac >= MAXARGS - 1)
			return (handle_parse_error(ret, "Max arguments exceeded", shell));
		ret = parseredirs(ret, cmd_ptr, shell);
	}
	exec_node->av[exec_node->ac] = 0;
	return (ret);
}