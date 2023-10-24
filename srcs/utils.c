/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:00 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/24 15:07:22 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork error\n");
	return (pid);
}

void	panic(char *s)
{
	printf("%s\n", s);
	exit(0);
}

// Replaces the chars at the end of the tokens with \0 so that
// execve has strings to work with
t_node	*nulterminate(t_node *node)
{
	int			i;
	t_execnode	*enode;
	t_redirnode	*rnode;
	t_pipenode	*pnode;

	if (node == 0)
		return (0);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		i = 0;
		while (enode->av[i])
			*enode->eav[i++] = 0;
		break ;
	case REDIR:
		rnode = (t_redirnode *)node;
		*rnode->efile = 0;
		nulterminate(rnode->execnode);
		break ;
	case PIPE:
		pnode = (t_pipenode *)node;
		nulterminate(pnode->left);
		nulterminate(pnode->right);
		break ;
	}
	return (node);
}

// Advances the trailing whitespace and returns 1 if the current char is in the tokens array
int	peek(char **pointer_to_cmd, char *tokens)
{
	char	whitespace[] = " \t\r\n\v";

	*pointer_to_cmd += ft_strspn(*pointer_to_cmd, whitespace);
	return (**pointer_to_cmd && ft_strchr(tokens, **pointer_to_cmd));
}
