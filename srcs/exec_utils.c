/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/25 19:55:17 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *cmd)
{
	char	*path;
	char	**paths;
	int		i;
	char	*ret;
	char	*tmp;

	path = ft_get_env("PATH", g_shell.env);
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	ret = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, F_OK | X_OK) == 0)
			break ;
		else
		{
			free(ret);
			ret = 0;
		}
	}
	ft_strarrfree(paths);
	if (!ret)
		ret = ft_strdup(cmd);
	return (ret);
}

void	execute_command(char *path, char **av)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) < 0)
		handle_file_not_found(path);
	if (S_ISREG(file_stat.st_mode))
	{
		set_signal_handling(1);
		execve(path, av, g_shell.env);
		if (errno == EACCES)
			handle_permission_denied(path);
		else
			handle_default_error();
	}
	else if (S_ISDIR(file_stat.st_mode))
	{
		if (ft_strchr(path, '/') != 0)
			handle_directory();
		else
			handle_file_not_found(path);
	}
}

void	handle_child_process(int *pipe, int direction, t_node *node)
{
	if (dup2_1(pipe[direction], direction) < 0)
		exit(errno);
	if (close_pipe(pipe) < 0)
		exit(errno);
	run_cmd(node);
}