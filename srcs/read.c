/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:07:29 by facu              #+#    #+#             */
/*   Updated: 2023/12/16 19:33:48 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(char **buf, char *prompt)
{
	if (prompt == 0)
		prompt = "🐚 ";
	set_signal_handling(0);
	*buf = readline(prompt);
	if (*buf == 0)
		return (-1);
	return (0);
}

int	read_heredoc(char *delimiter)
{
	char	*line;
	int		fd[2];

	if (pipe_1(fd) == -1)
		return (-1);
	while (prompt(&line, "🐚 hdoc ") >= 0)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
