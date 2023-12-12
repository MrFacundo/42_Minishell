/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:51:28 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Sets parsing error status, prints errorm returns unnmodified node */
t_node	*handle_parse_error(t_node *ret, const char *error_message,
		t_shell *shell)
{
	shell->parsing_status = TOKEN_ERROR;
	if (error_message)
		print_error(1, error_message);
	return (ret);
}

/* Reverses the order of redirection nodes, returns the new REDIR root node  */
t_node	*reverse_redir_nodes_help(t_node *root)
{
	t_node	*prev;
	t_node	*current;
	t_node	*next;

	prev = 0;
	current = root;
	next = 0;
	while (current->type == REDIR || current->type == HEREDOC)
	{
		next = ((t_redirnode *)current)->node;
		((t_redirnode *)current)->node = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

t_node	*parseredirs_help(t_node *node, char **tkn_ptr, int token)
{
	t_node	*ret;

	if (token == '<')
		ret = redircmd(node, *tkn_ptr, O_RDONLY, STDIN_FILENO);
	else if (token == '>')
		ret = redircmd(node, *tkn_ptr, O_WRONLY | O_CREAT | O_TRUNC,
				STDOUT_FILENO);
	else if (token == '+')
		ret = redircmd(node, *tkn_ptr, O_WRONLY | O_CREAT | O_APPEND,
				STDOUT_FILENO);
	return (ret);
}
