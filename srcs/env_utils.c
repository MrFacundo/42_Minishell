/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:27:22 by facu              #+#    #+#             */
/*   Updated: 2023/11/21 01:34:17 by facu             ###   ########.fr       */
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

void	add_key_to_env(char *key, char *value, int i)
{
	int		new_size;
	char	**new_env_array;
	int		j;
	char	*temp;

	new_size = i + 2;
	new_env_array = malloc(sizeof(char *) * new_size);
	j = 0;
	while (j < i)
	{
		new_env_array[j] = strdup(g_shell.env[j]);
		j++;
	}
	temp = ft_strjoin(key, "=");
	new_env_array[i] = ft_strjoin(temp, value);
	free(temp);
	ft_strarrfree(g_shell.env);
	new_env_array[new_size - 1] = 0;
	g_shell.env = new_env_array;
}
