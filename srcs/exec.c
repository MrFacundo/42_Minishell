/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/22 21:04:46 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recursively executes the command tree
void	runcmd(t_node *node)
{
	t_execnode	*enode;

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
	default:
		panic("runcmd");
	}
	exit(0);
}
