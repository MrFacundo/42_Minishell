/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:47 by facu              #+#    #+#             */
/*   Updated: 2023/12/01 15:54:51 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**initialize_env(char **envp)
{
	int	i;
	int	size;
	char	**env;
	i = 0;
	size = 0;
	while (envp[size])
		size++;
	env = ft_calloc((size + 1), sizeof(char *));
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
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

void	set_env(char *key_value, t_shell *shell)
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
		while (shell->env[i])
			if (key_matches(key, shell->env[i++]))
				return ;
	}
	else
	{
		while (shell->env[i])
		{
			if (key_matches(key, shell->env[i]))
				return (update_key(key, value, i, shell));
			i++;
		}
	}
	add_key_to_env(key, value, shell);
	free(key);
	free(value);
}

void	unset_env(char *key, t_shell *shell)
{
	size_t	env_size;
	size_t	new_env_size;
	size_t	i;
	size_t	j;
	char	**new_env_array;

	env_size = ft_strarrsize(shell->env);
	new_env_size = env_size;
	new_env_array = ft_calloc((new_env_size + 1), sizeof(char *));
	i = 0;
	j = 0;
	while (i < env_size)
	{
		if (!key_matches(key, shell->env[i]))
		{
			new_env_array[j] = ft_strdup(shell->env[i]);
			j++;
		}
		i++;
	}
	ft_strarrfree(shell->env);
	shell->env = new_env_array;
}

void	print_env(char **env)
{
	char	**env_copy;
	char	**current_string;

	env_copy = ft_strarrcpy(env);
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
