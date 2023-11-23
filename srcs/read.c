/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:07:29 by facu              #+#    #+#             */
/*   Updated: 2023/11/23 18:16:25 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_cmd(char **buf)
{
	set_signal_handling(0);
	*buf = readline("ms > ");
	if (*buf == 0)
		return (-1);
	return (0);
}

void	read_heredoc(t_heredocnode *node, char *delimiter, char *edelimiter)
{
	char	*line;
	int		fd[2];

	if (pipe_1(fd) == -1)
		return ;
	node->fd = fd[0];
	while (1)
	{
        line = readline("> ");
        if (ft_strncmp(line, delimiter, edelimiter - delimiter) == 0) {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
	}
	close(fd[1]);
}
