/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/20 11:21:35 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Initializes parsing error status, sets root node */
t_node	*parse_cmd(char *cmd, t_shell *shell)
{
	t_node	*node;

	shell->parsing_status = 0;
	node = parsepipe(&cmd, shell);
	if (shell->parsing_status == TOKEN_ERROR)
		g_exit_status = TOKEN_ERROR;
	return (node);
}

/* Returns an EXEC node if the command contains no pipes,
	otherwise returns a PIPE node */
t_node	*parsepipe(char **cmd_ptr, t_shell *shell)
{
	t_node	*left;

	left = parseexec(cmd_ptr, shell);
	if (shell->parsing_status == 0 && peek(cmd_ptr, "|"))
	{
		get_token(cmd_ptr, 0, shell);
		if ((left->type == EXEC && ((t_execnode *)left)->ac == 0)
			|| **cmd_ptr == '\0'
			|| peek(cmd_ptr, "|()&;<>"))
			return (handle_parse_error(left, "Parse error near pipe", shell));
		return (pipenode(left, parsepipe(cmd_ptr, shell)));
	}
	return (left);
}

/* Reverses the order of REDIR nodes,
	sets the first redirection node to point to the EXEC node,
	returns the new REDIR root node */
t_node	*reverse_redir_nodes(t_node *node)
{
	t_node	*new_root;
	t_node	*exec_node;

	exec_node = node;
	while (exec_node->type == REDIR || exec_node->type == HEREDOC)
		exec_node = ((t_redirnode *)exec_node)->node;
	new_root = reverse_redir_nodes_help(node);
	((t_redirnode *)node)->node = exec_node;
	return (new_root);
}

/* Parses redirections and heredocs, returns the REDIR root node
	if any, otherwise returns the EXEC node */
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
			return (handle_parse_error(node, "Parse error near redirection",
					shell));
		else if (token == '-')
			node = heredoccmd(node, tkn_ptr);
		else
			node = parseredirs_help(node, &tkn_ptr, token);
	}
	if (node->type == REDIR || node->type == HEREDOC)
		return (reverse_redir_nodes(node));
	return (node);
}

/* Parses the command and its arguments and checks for redirections,
	returns a REDIR node if any, otherwise returns an EXEC node */
t_node	*parseexec(char **cmd_ptr, t_shell *shell)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*tkn_ptr;
	int			token;

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
	if (exec_node->av[0] == 0)
	ret = parseredirs(ret, cmd_ptr, shell);
	return (ret);
}
