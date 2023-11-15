/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/15 12:19:05 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *cmd)
{
	char	*path;
	char	**paths;
	int		i;
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	path = ft_get_env("PATH", g_shell.env);
	paths = ft_split(path, ':');
	i = 0;
	ret = 0;
	while (paths[i] && !ret)
	{
		tmp1 = ft_strjoin(paths[i++], "/");
		tmp2 = ft_strjoin(tmp1, cmd);
		if (access(tmp2, F_OK | X_OK) == 0)
		{
			ret = tmp2;
			free(tmp1);
		}
		else
		{
			free(tmp1);
			free(tmp2);
		}
	}
	free_array(paths);
	if (!ret)
		ret = ft_strdup(cmd);
	return (ret);
}

void	execute_command(char *path, char **av)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		handle_file_not_found(path);
	if (S_ISREG(file_stat.st_mode))
	{
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
	t_execnode	*enode;
	t_redirnode	*rnode;
	t_pipenode	*pnode;
	int			p[2];
	char		*path;
	int			status;
	pid_t		left_side_process;
	pid_t		rigth_side_process;

	if (node == 0)
		exit(0);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		if (enode->av[0] == 0)
			exit(0);
		if (is_builtin(node))
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
		break ;
	case REDIR:
		rnode = (t_redirnode *)node;
		close(rnode->fd);
		if (open_1(rnode->file, rnode->mode) < 0)
			exit(ENOENT);
		runcmd(rnode->execnode);
		break ;
	case PIPE:
		pnode = (t_pipenode *)node;
		if (pipe_1(p) < 0)
			exit(1);
		left_side_process = fork_1();
		if (left_side_process == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pnode->left);
			break ;
		}
		rigth_side_process = fork_1();
		if (rigth_side_process == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
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
