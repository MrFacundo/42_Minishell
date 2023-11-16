/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:47 by facu              #+#    #+#             */
/*   Updated: 2023/11/15 17:13:13 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_env(t_shell *g_shell, char **envp)
{
	int	i;
	int	size;

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
	size_t	key_length;

	i = 0;
	value = 0;
	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(key, env[i], key_length) == 0
			&& env[i][key_length] == '=')
		{
			value = ft_strdup(env[i] + key_length + 1);
			break ;
		}
		i++;
	}
	return (value);
}