/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:05:37 by facu              #+#    #+#             */
/*   Updated: 2023/12/19 19:36:35 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(const char *message)
{
	print_error(2, "cd", message);
	g_exit_status = EXIT_FAILURE;
}

char	*get_target_path(char **av, t_shell *shell)
{
	if (av[1] == 0)
		return (ft_get_env("HOME", shell->env));
	else if (ft_strcmp(av[1], "-") == 0)
		return (ft_get_env("OLDPWD", shell->env));
	else
		return (av[1]);
}

void	update_env_paths(char *pwd, char *oldpwd, t_shell *shell)
{
	char	*temp;

	temp = ft_strjoin("PWD=", pwd);
	set_env(temp, shell);
	free(temp);
	temp = ft_strjoin("OLDPWD=", oldpwd);
	set_env(temp, shell);
	free(temp);
}

void	run_cd_helper(char *path, char *oldpwd, char **av, t_shell *shell)
{
	char	*pwd;

	if (!path)
	{
		print_cd_error("Failed to get path");
	}
	else
	{
		if (chdir(path) == -1)
			print_cd_error(strerror(errno));
		if (!g_exit_status)
		{
			pwd = getcwd(NULL, 0);
			update_env_paths(pwd, oldpwd, shell);
			free(pwd);
			if (!av[1])
				free(path);
		}
	}
}

void	run_cd(char **av, t_shell *shell)
{
	char	*oldpwd;
	char	*path;

	if (av[1] && av[2])
		return (print_cd_error("too many arguments"));
	oldpwd = getcwd(NULL, 0);
	path = get_target_path(av, shell);
	run_cd_helper(path, oldpwd, av, shell);
	free(oldpwd);
}
