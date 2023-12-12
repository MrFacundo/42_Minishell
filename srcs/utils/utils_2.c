/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:55:21 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_1(char *file, int flags)
{
	mode_t	mode;
	int		fd;

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
