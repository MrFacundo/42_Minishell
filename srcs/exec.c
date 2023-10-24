/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/24 17:28:39 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recursively executes the command tree
void	runcmd(t_node *node)
{
	t_execnode	*enode;
	t_redirnode	*rnode;
	t_pipenode	*pnode;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;                                                                                                                                    
	int p[2];

	if (node == 0)
		exit(0);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		if (enode->av[0] == 0)
			exit(0);
		// TODO: use execve instead of execvp
		printf("//output:\n");
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
	case PIPE:
		pnode = (t_pipenode *)node;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pnode->left);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pnode->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
		break ;
	default:
		panic("runcmd");
	}
	exit(0);
}
