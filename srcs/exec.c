/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:25 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/31 19:51:08 by facu             ###   ########.fr       */
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
	return (ret);
}

void	execute_command(char *path, char **av, char **env)
{
	execve(path, av, env);
	// exit code and error message will be provided by execve, errno and strerror
	printf("exec %s failed\n", av[0]);
	// free path?
	exit(0);
}

// Recursively executes the command tree
// DONT DIVIDE INTO SMALLER FUNCTIONS UNTIL LOGIC IS CLEAR
void	runcmd(t_node *node)
{
	t_execnode	*enode;
	t_redirnode	*rnode;
	t_pipenode	*pnode;
	mode_t		mode;
	int			p[2];
	char		*path;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (node == 0)
		exit(0);
	switch (node->type)
	{
	case EXEC:
		enode = (t_execnode *)node;
		if (enode->av[0] == 0)
			exit(0);
		if (ft_strchr(enode->av[0], '/') == 0)
			path = find_path(enode->av[0]);
		else
			path = ft_strdup(enode->av[0]);
		printf("//path: %s\n", path);
		execute_command(path, enode->av, g_shell.env);
		break ;
	case REDIR:
		rnode = (t_redirnode *)node;
		close(rnode->fd);
		if (open(rnode->file, rnode->mode, mode) < 0)
			panic("open failed");
		runcmd(rnode->execnode);
		break ;
	case PIPE:
		pnode = (t_pipenode *)node;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pnode->left);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pnode->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
		break ;
	default:
		panic("runcmd");
	}
	exit(0);
}
