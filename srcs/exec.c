/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/24 14:27:55 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recursively executes the command tree
void	runcmd(t_node *node)
{
	t_execnode	*enode;
	t_redirnode	*rnode;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if (node == 0)
		exit(0);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		if (enode->av[0] == 0)
			exit(0);
		// TODO: use execve instead of execvp
		execvp(enode->av[0], enode->av);
		printf("exec %s failed\n", enode->av[0]);
		break ;
	case REDIR:
		rnode = (t_redirnode *)node;
		close(rnode->fd);
		if (open(rnode->file, rnode->mode, mode) < 0)
			panic("open failed");
		runcmd(rnode->execnode);
		break ;
	default:
		panic("runcmd");
	}
	exit(0);
}
