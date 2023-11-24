/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:47 by facu              #+#    #+#             */
/*   Updated: 2023/11/24 16:43:07 by facu             ###   ########.fr       */
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

void	set_env(char *key_value)
{
	char	*key;
	char	*value;
	int		i;

	key = extract_key(key_value);
	value = extract_value(key_value);
	i = 0;
	if (!key)
		return ;
	if (!*value)
	{
		while (g_shell.env[i])
			if (key_matches(key, g_shell.env[i++]))
				return ;
	}
	else
	{
		while (g_shell.env[i])
		{
			if (key_matches(key, g_shell.env[i]))
				return (update_key(key, value, i));
			i++;
		}
	}
	add_key_to_env(key, value);
	free(key);
	free(value);
}

void	unset_env(char *key)
{
	size_t	env_size;
	size_t	new_env_size;
	size_t	i;
	size_t	j;
	char	**new_env_array;

	env_size = ft_strarrsize(g_shell.env);
	new_env_size = env_size;
	new_env_array = malloc(sizeof(char *) * new_env_size);
	i = 0;
	j = 0;
	while (i < env_size)
	{
		if (!key_matches(key, g_shell.env[i]))
		{
			new_env_array[j] = ft_strdup(g_shell.env[i]);
			j++;
		}
		i++;
	}
	ft_strarrfree(g_shell.env);
	new_env_array[new_env_size - 1] = 0;
	g_shell.env = new_env_array;
}

void	print_env()
{
	char	**env_copy;
	char	**current_string;

	env_copy = ft_strarrcpy(g_shell.env);
	if (env_copy == 0)
		return ;
	ft_strarrbsort(env_copy);
	current_string = env_copy;
	while (*current_string)
	{
		ft_putstr_fd(*current_string, 1);
		ft_putchar_fd('\n', 1);
		++current_string;
	}
	ft_strarrfree(env_copy);
}
