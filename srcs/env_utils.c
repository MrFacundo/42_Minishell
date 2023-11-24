/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:27:22 by facu              #+#    #+#             */
/*   Updated: 2023/11/24 17:35:44 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_key(char *key_value)
{
	return (ft_substr(key_value, 0, ft_strchr(key_value, '=') - key_value));
}

char	*extract_value(char *key_value)
{
	return (ft_substr(key_value, ft_strchr(key_value, '=') - key_value + 1,
			ft_strlen(key_value)));
}

int	key_matches(char *key, char *env)
{
	size_t	key_length;

	key_length = ft_strlen(key);
	if (ft_strncmp(key, env, key_length) == 0 && env[key_length] == '=')
		return (1);
	return (0);
}

void	update_key(char *key, char *value, int i)
{
	char	*temp;
	char	*new_env;

	temp = ft_strjoin(key, "=");
	new_env = ft_strjoin(temp, value);
	free(temp);
	free(g_shell.env[i]);
	g_shell.env[i] = new_env;
}

void	add_key_to_env(char *key, char *value)
{
	size_t	env_size;
	size_t	new_env_size;
	size_t	j;
	char	**new_env_array;
	char	*temp;

	env_size = ft_strarrsize(g_shell.env);
	new_env_size = env_size + 2;
	new_env_array = ft_calloc((new_env_size + 1), sizeof(char *));
	j = 0;
	while (j < env_size)
	{
		new_env_array[j] = ft_strdup(g_shell.env[j]);
		j++;
	}
	temp = ft_strjoin(key, "=");
	new_env_array[env_size] = ft_strjoin(temp, value);
	free(temp);
	ft_strarrfree(g_shell.env);
	g_shell.env = new_env_array;
}

int	is_valid_identifier(const char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '=')
			return (0);
		++str;
	}
	return (1);
}
