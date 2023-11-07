/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:47 by facu              #+#    #+#             */
/*   Updated: 2023/11/07 20:31:08 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_env(t_shell *g_shell, char **envp)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	g_shell->env = malloc(sizeof(char *) * (size + 1));
	while (envp[i])
	{
		g_shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
	g_shell->env[i] = 0;
}

char	*ft_get_env(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	value = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], ft_strlen(key)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(key) + 1);
			break ;
		}
		i++;
	}
	return (value);
}