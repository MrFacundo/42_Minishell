/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:04:36 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Free an EXEC node
void	free_exec_node(t_execnode *exec_node)
{
	int	i;

	i = 0;
	while (exec_node->av[i])
		free(exec_node->av[i++]);
	free(exec_node);
}

// Free a REDIR node
void	free_redir_node(t_redirnode *redir_node)
{
	free_tree(redir_node->node);
	free(redir_node->file);
	free(redir_node);
}

// Free a PIPE node
void	free_pipe_node(t_pipenode *pipe_node)
{
	free_tree(pipe_node->left);
	free_tree(pipe_node->right);
	free(pipe_node);
}

// Free a HEREDOC node
void	free_heredoc_node(t_heredocnode *heredoc_node)
{
	free_tree(heredoc_node->execnode);
	free(heredoc_node);
}

// Free the tree starting from the given node
void	free_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == EXEC)
		free_exec_node((t_execnode *)node);
	else if (node->type == REDIR)
		free_redir_node((t_redirnode *)node);
	else if (node->type == PIPE)
		free_pipe_node((t_pipenode *)node);
	else if (node->type == HEREDOC)
		free_heredoc_node((t_heredocnode *)node);
}
