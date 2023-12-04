/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/04 12:58:57 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**paths;
	int		i;
	char	*ret;
	char	*tmp;

	ret = 0;
	path = ft_get_env("PATH", shell->env);
	if (!path)
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
	free(path);
	i = 0;
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

void	execute_command(char *path, char **av, t_shell *shell)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) < 0)
		handle_file_not_found(path);
	if (S_ISREG(file_stat.st_mode))
	{
		set_signal_handling(1);
		execve(path, av, shell->env);
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

void	run_external(t_node *node, int *status, t_shell *shell)
{
	t_execnode	*enode;
	char		*path;

	enode = (t_execnode *)node;
	if (enode->av[0] == 0)
		exit(0);
	if (ft_strchr(enode->av[0], '/') == 0)
		path = find_path(enode->av[0], shell);
	else
		path = ft_strdup(enode->av[0]);
	if (fork_1() == 0)
		execute_command(path, enode->av, shell);
	wait(status);
	free(path);
}

void	handle_child_process(int *pipe, int direction, t_node *node, t_shell *shell)
{
	if (dup2_1(pipe[direction], direction) < 0)
		exit(errno);
	if (close_pipe(pipe) < 0)
		exit(errno);
	run_cmd(node, shell);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status= WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status= WTERMSIG(status) + 128;
}
