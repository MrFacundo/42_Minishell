/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_finding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 00:13:55 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_full_path(const char *directory, const char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(directory, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*try_access_and_free(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	free(path);
	return (0);
}

char	*find_valid_path(char **paths, const char *cmd)
{
	char	*ret;
	int		i;
	char	*full_path;

	ret = 0;
	i = 0;
	while (paths[i] && !ret)
	{
		full_path = build_full_path(paths[i], cmd);
		ret = try_access_and_free(full_path);
		++i;
	}
	return (ret);
}

char	*find_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**paths;
	char	*valid_path;

	if (cmd == 0 || *cmd == '\0')
		return (0);
	path = ft_get_env("PATH", shell->env);
	if (!path)
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
	free(path);
	valid_path = find_valid_path(paths, cmd);
	ft_strarrfree(paths);
	if (valid_path)
		return (valid_path);
	else
		return (ft_strdup(cmd));
}
