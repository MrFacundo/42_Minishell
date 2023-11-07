/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:00 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/07 21:13:51 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Replaces the chars at the end of the tokens with \0
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

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	open_1(char *file, int flags)
{
	mode_t		mode;
	int	fd;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(file, flags, mode);
	if (fd < 0)
		print_error(file);
	return (fd);
}

int	pipe_1(int *p)
{
	int	pipefd;

	pipefd = pipe(p);
	if (pipefd < 0)
		print_error("pipe");
	return (pipefd);
}

int	fork_1(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error("fork");
	return (pid);
}

void	print_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}