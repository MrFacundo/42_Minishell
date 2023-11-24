/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:55 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/24 16:03:54 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*execnode(void)
{
	t_execnode	*node;

	node = ft_calloc(1, sizeof(t_execnode));
	node->type = EXEC;
	return ((t_node *)node);
}

t_node	*redircmd(t_node *execnode, char *file, char *efile, int mode, int fd)
{
	t_redirnode	*node;

	node = ft_calloc(1, sizeof(t_redirnode));
	node->type = REDIR;
	node->execnode = execnode;
	node->file = file;
	node->efile = efile;
	node->mode = mode;
	node->fd = fd;
	return ((t_node *)node);
}

t_node	*pipenode(t_node *left, t_node *right)
{
	t_pipenode	*node;

	node = ft_calloc(1, sizeof(t_pipenode));
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return ((t_node *)node);
}

t_node	*heredoccmd(t_node *execnode, char *delimiter, char *edelimiter)
{
	t_heredocnode	*node;

	node = ft_calloc(1, sizeof(t_heredocnode));
	node->type = HEREDOC;
	node->execnode = execnode;
	node->fd = read_heredoc(delimiter, edelimiter);
	return ((t_node *)node);
}
