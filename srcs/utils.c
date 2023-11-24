/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:00 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/24 22:43:34 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Advances the trailing whitespace and returns 1 if the current char is in the tokens array
int	peek(char **pointer_to_cmd, char *tokens)
{
	char	whitespace[] = " \t\r\n\v";

	*pointer_to_cmd += ft_strspn(*pointer_to_cmd, whitespace);
	return (**pointer_to_cmd && ft_strchr(tokens, **pointer_to_cmd));
}

int	open_1(char *file, int flags)
{
	mode_t		mode;
	int	fd;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(file, flags, mode);
	if (fd < 0)
		print_error(1, strerror(errno));
	return (fd);
}

int	pipe_1(int *p)
{
	int	pipefd;

	pipefd = pipe(p);
	if (pipefd < 0)
		print_error(1, strerror(errno));
	return (pipefd);
}

int	fork_1(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(1, strerror(errno));
	return (pid);
}

int	dup2_1(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret < 0)
		print_error(1, strerror(errno));
	return (ret);
}

int	close_pipe(int *p)
{
	int	ret;

	ret = close(p[0]);
	if (ret < 0)
		print_error(1, strerror(errno));
	ret = close(p[1]);
	if (ret < 0)
		print_error(1, strerror(errno));
	return (ret);
}

void	print_error(int n, ...)
{
	va_list	args;

	va_start(args, n);
	ft_putstr_fd("minishell", 2);
	while (n--)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(va_arg(args, char *), 2);
	}
	ft_putstr_fd("\n", 2);
	va_end(args);
}
