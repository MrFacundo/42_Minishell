/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:17:02 by facu              #+#    #+#             */
/*   Updated: 2023/12/22 15:43:44 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	Returns 1 or 0 depending on whether the command is a builtin
	and whether it can be executed in a nested context or not */
int	is_builtin(t_node *node)
{
	t_execnode	*enode;
	char		**commands;
	int			is_builtin;

	commands = (char *[]){"echo", "export", "unset", "cd", "exit", "pwd", "env",
		0};
	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	is_builtin = ft_strarrfind(commands, enode->av[0]);
	return (is_builtin);
}

void	run_env(t_shell *shell)
{
	int		i;
	char	*env_var;

	i = 0;
	while ((shell->env[i]))
	{
		env_var = shell->env[i++];
		if (env_var[ft_strlen(env_var) - 1] == '=')
			continue ;
		ft_putstr_fd(env_var, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_exit_status = EXIT_SUCCESS;
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
	else if (ft_strcmp(enode->av[0], "cd") == 0)
		run_cd(enode->av, shell);
	else if (ft_strcmp(enode->av[0], "env") == 0)
		run_env(shell);
}
