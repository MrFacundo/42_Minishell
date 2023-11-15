/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/15 11:35:21 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

int	is_builtin(t_node *node)
{
	int		is_builtin;
	t_execnode	*enode;

	is_builtin = 0;
	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	if (enode->av[0] == 0)
		return (0);
	if (ft_strcmp(enode->av[0], "cd") == 0
		|| ft_strcmp(enode->av[0], "echo") == 0
		|| ft_strcmp(enode->av[0], "exit") == 0
		|| ft_strcmp(enode->av[0], "export") == 0
		|| ft_strcmp(enode->av[0], "pwd") == 0
		|| ft_strcmp(enode->av[0], "unset") == 0)
		is_builtin = 1;
	return (is_builtin);
}

void	run_exit(char **av)
{
	int	exit_code;

	exit_code = 0;
	if (av[2])
	{
		print_error(1, "exit: too many arguments");
		exit_code = 1;
		return ;
	}
	else if (av[1])
		exit_code = ft_atoi(av[1]);
	exit(exit_code);
}

void	run_echo(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (av[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	run_builtin(t_node *node)
{
	t_execnode	*enode;

	enode = (t_execnode *)node;
	if (ft_strcmp(enode->av[0], "exit") == 0)
		run_exit(enode->av);
	else if (ft_strcmp(enode->av[0], "echo") == 0)
		run_echo(enode->av);
	// else if (ft_strcmp(enode->av[0], "cd") == 0)
	// 	run_cd(enode->av);
	// else if (ft_strcmp(enode->av[0], "export") == 0)
	// 	run_export(enode->av);
	// else if (ft_strcmp(enode->av[0], "pwd") == 0)
	// 	run_pwd(enode->av);
	// else if (ft_strcmp(enode->av[0], "unset") == 0)
	// 	run_unset(enode->av);
	// exit code should be set to 0 after a successful builtin run
}

int	main(int argc, char **argv, char **envp)
{
	char *buf;
	t_node *node;
	int		status;

  	// TODO: ensure three file descriptors are open
	(void)argc;
	(void)argv;
	initialize_env(&g_shell, envp);
	g_shell.exit_code = 0;
	while (getcmd(&buf) >= 0)
	{
		if (*buf)
			add_history(buf);
		node = parsecmd(buf);
		if (node == 0)
			continue ;
		if (is_builtin(node)) // TODO: move to runcmd
			run_builtin(node);
		else
			if (fork_1() == 0)
				runcmd(node);
		wait(&status);
		g_shell.exit_code = WEXITSTATUS(status);
		
	}
	return (0);
}

int	getcmd(char **buf)
{
	*buf = readline("ms > ");
	if (*buf == 0) // Ctrl+D was pressed (EOF)
		return (-1);
	return (0);
}
