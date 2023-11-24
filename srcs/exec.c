/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/24 21:27:26 by ftroiter         ###   ########.fr       */
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

// Recursively executes the command tree
// DONT DIVIDE INTO SMALLER FUNCTIONS UNTIL LOGIC IS CLEAR
void	runcmd(t_node *node)
{
	t_execnode		*enode;
	t_redirnode		*rnode;
	t_pipenode		*pnode;
	t_heredocnode	*hnode;
	int			p[2];
	char		*path;
	int			status;
	pid_t		left_side_process;
	pid_t		rigth_side_process;

	if (node == 0)
		exit(0);
	set_signal_handling(2);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		if (enode->av[0] == 0)
			exit(0);
		if (is_builtin(node, 1))
		{
			run_builtin(node);
			break;
		}
		if (ft_strchr(enode->av[0], '/') == 0)
			path = find_path(enode->av[0]);
		else
			path = ft_strdup(enode->av[0]);
		if (fork_1() == 0)
			execute_command(path, enode->av);
		wait(&status);
		free(path);
		break ;
	case REDIR:
		rnode = (t_redirnode *)node;
		close(rnode->fd);
		if (open_1(rnode->file, rnode->mode) < 0)
			exit(ENOENT);
		runcmd(rnode->execnode);
		break ;
	case HEREDOC:
		hnode = (t_heredocnode *)node;
		if (dup2_1(hnode->fd, 0) < 0)
			exit(errno);
		close(hnode->fd);
		runcmd(((t_heredocnode *)node)->execnode);
		break ;
	case PIPE:
		pnode = (t_pipenode *)node;
		if (pipe_1(p) < 0)
			exit(1);
		left_side_process = fork_1();
		if (left_side_process < 0)
			exit(errno);
		if (left_side_process == 0)
		{
			if (dup2_1(p[1], 1) < 0)
				exit(errno);
			if (close_pipe(p) < 0)
				exit(errno);
			runcmd(pnode->left);
			break ;
		}
		rigth_side_process = fork_1();
		if (rigth_side_process < 0)
			exit(errno);
		if (rigth_side_process == 0)
		{
			if (dup2_1(p[0], 0) < 0)
				exit(errno);
			if (close_pipe(p) < 0)
				exit(errno);
			runcmd(pnode->right);
			break ;
		}
		close(p[0]);
		close(p[1]);
		waitpid(left_side_process, &status, 0);
		waitpid(rigth_side_process, &status, 0);
		break ;
	default:
		print_error(1, "runcmd");
	}
	if (WIFEXITED(status))
		g_shell.exit_code = WEXITSTATUS(status);
	else
		g_shell.exit_code = 0;
	exit(g_shell.exit_code);
}
