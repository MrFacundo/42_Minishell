/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:17:02 by facu              #+#    #+#             */
/*   Updated: 2023/11/15 16:03:47 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_helper(const char *command, const char *builtin_commands[])
{
	int	i;

	i = 0;
	while (builtin_commands[i] != 0)
		if (!ft_strcmp(command, builtin_commands[i++]))
			return (1);
	return (0);
}

int	is_builtin(t_node *node, int nested_execution)
{
	t_execnode	*enode;
	const char	*non_nested_commands[] = {"cd", "exit", 0};
	const char	*commands[] = {"echo", "export", "unset", "cd", "exit", "pwd", 0};
	int			is_non_nested_builtin;
	int			is_builtin;

	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	is_non_nested_builtin = is_builtin_helper(enode->av[0], non_nested_commands);
	is_builtin = is_builtin_helper(enode->av[0], commands);
	if (nested_execution)
		if (is_non_nested_builtin)
			exit(0);
	return (is_builtin);
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

int	has_alphabetic_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (ft_isalpha(str[i++]))
			return (1);
	return (0);
}

void	run_exit(char **av)
{
	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_shell.exit_code = 1;
	}
	else if (has_alphabetic_chars(av[1]))
	{
		print_error(2, "exit", "numeric argument required");
		g_shell.exit_code = 2;
	}
	else if (av[1])
		g_shell.exit_code = ft_atoi(av[1]);
	exit(g_shell.exit_code);
}

void	run_echo(char **av)
{
	int i;

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