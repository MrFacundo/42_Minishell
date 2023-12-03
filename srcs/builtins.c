/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:17:02 by facu              #+#    #+#             */
/*   Updated: 2023/12/03 02:03:21 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Returns 1 or 0 depending on whether the command is a builtin
	and whether it can be executed in a nested context or not */
int	is_builtin(t_node *node, int nested_context)
{
	t_execnode	*enode;
	char	*commands[] = {"echo", "export", "unset", "cd", "exit", "pwd",
			0};
	char	*non_nested_commands[] = {"cd", "exit", 0};
	int			is_builtin;
	int			is_non_nested_builtin;

	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	is_builtin = ft_strarrfind(commands, enode->av[0]);
	is_non_nested_builtin = ft_strarrfind(non_nested_commands, enode->av[0]);
	if (nested_context)
		if (is_non_nested_builtin)
			exit(0);
	return (is_builtin);
}

void	run_export(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	if (av[1] == 0)
	{
		print_env(shell->env);
		g_exit_status= EXIT_SUCCESS;
	}
	else
	{
		while (av[i])
		{
			if (!is_valid_identifier(av[i]))
			{
				print_error(2, "export", "not a valid identifier");
				g_exit_status= 1;
				return ;
			}
			else
				set_env(av[i], shell);
			++i;
		}
		g_exit_status= EXIT_SUCCESS;
	}
}

void	run_pwd()
{
	char	s[PATH_MAX];

	getcwd(s, PATH_MAX);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	g_exit_status= EXIT_SUCCESS;
}

void	run_unset(char **av, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (is_valid_identifier(av[i]))
		{
			j = 0;
			while(shell->env[j])
			{
				if (key_matches(av[i], shell->env[j]))
				{
					unset_env(av[i], shell);
					break ;
				}
				j++;
			}
		}
		else
		{
			print_error(2, "unset", "not a valid identifier");
			g_exit_status= 1;
		}
		i++;
	}
}

void	run_exit(char **av)
{
	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_exit_status= 1;
	}
	else if (has_alphabetic_chars(av[1]))
	{
		print_error(2, "exit", "numeric argument required");
		g_exit_status= 2;
	}
	else if (av[1])
		g_exit_status= ft_atoi(av[1]);
	exit(g_exit_status);
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
	g_exit_status= EXIT_SUCCESS;

}

void	run_builtin(t_node *node, t_shell *shell)
{
	t_execnode	*enode;

	enode = (t_execnode *)node;
	if (ft_strcmp(enode->av[0], "exit") == 0)
		run_exit(enode->av);
	else if (ft_strcmp(enode->av[0], "echo") == 0)
		run_echo(enode->av);
	else if (ft_strcmp(enode->av[0], "export") == 0)
		run_export(enode->av, shell);
	else if (ft_strcmp(enode->av[0], "pwd") == 0)
		run_pwd();
	else if (ft_strcmp(enode->av[0], "unset") == 0)
		run_unset(enode->av, shell);
	// else if (ft_strcmp(enode->av[0], "cd") == 0)
	// 	run_cd(enode->av);
	// else if (ft_strcmp(enode->av[0], "env") == 0)
	// 	run_env(enode->av);
}