/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:17:02 by facu              #+#    #+#             */
/*   Updated: 2023/11/21 01:33:06 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Returns 1 or 0 depending on whether the command is a builtin
	and whether it can be executed in a nested context or not
*/
int	is_builtin(t_node *node, int nested_context)
{
	t_execnode	*enode;
	const char	*commands[] = {"echo", "export", "unset", "cd", "exit", "pwd",
			0};
	const char	*non_nested_commands[] = {"cd", "exit", 0};
	int			is_builtin;
	int			is_non_nested_builtin;

	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	is_builtin = is_builtin_helper(enode->av[0], commands);
	is_non_nested_builtin = is_builtin_helper(enode->av[0],
			non_nested_commands);
	if (nested_context)
		if (is_non_nested_builtin)
			exit(0);
	return (is_builtin);
}

void	bubble_sort_string_array(char **strings)
{
	size_t	count;
	size_t	i;
	size_t	j;
	char	*temp;

	if (strings == 0)
		return ;
	count = 0;
	while (strings[count] != 0)
		++count;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(strings[j], strings[j + 1]) > 0)
			{
				temp = strings[j];
				strings[j] = strings[j + 1];
				strings[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}

void	print_env()
{
	char	**env_copy;
	char	**current_string;

	env_copy = ft_strarrcpy(g_shell.env);
	if (env_copy == 0)
		return ;
	bubble_sort_string_array(env_copy);
	current_string = env_copy;
	while (*current_string)
	{
		ft_putstr_fd(*current_string, 1);
		ft_putchar_fd('\n', 1);
		++current_string;
	}
	ft_strarrfree(env_copy);
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	is_valid_identifier(const char *str)
{
	if (ft_isdigit(str[0]))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '=')
			return (0);
		++str;
	}
	return (1);
}

void	process_export_args(char **av)
{
	int	i;
	i = 1;

	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
			print_error(2, "export", "not a valid identifier");
		else
			update_env(av[i]);
		++i;
	}
}

void	run_export(char **av)
{
	if (av[1] == 0)
		print_env();
	else
		process_export_args(av);
}

void	run_builtin(t_node *node)
{
	t_execnode	*enode;

	enode = (t_execnode *)node;
	if (ft_strcmp(enode->av[0], "exit") == 0)
		run_exit(enode->av);
	else if (ft_strcmp(enode->av[0], "echo") == 0)
		run_echo(enode->av);
	else if (ft_strcmp(enode->av[0], "export") == 0)
		run_export(enode->av);
	// else if (ft_strcmp(enode->av[0], "cd") == 0)
	// 	run_cd(enode->av);
	// else if (ft_strcmp(enode->av[0], "pwd") == 0)
	// 	run_pwd(enode->av);
	// else if (ft_strcmp(enode->av[0], "unset") == 0)
	// 	run_unset(enode->av);
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
