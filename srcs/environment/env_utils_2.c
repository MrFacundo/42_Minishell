/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:40 by facu              #+#    #+#             */
/*   Updated: 2023/12/26 17:03:47 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_key(char *key_value)
{
	return (ft_substr(key_value, 0, ft_strchr(key_value, '=') - key_value));
}

char	*extract_value(char *key_value)
{
	return (ft_substr(key_value, ft_strchr(key_value, '=') - key_value + 1,
			ft_strlen(key_value)));
}

int	find_key_index(char *key, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (key_matches(key, shell->env[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup_env(char *str)
{
	int	first_equal;
	char *copy;
	int	i;
	int	j;
	
	first_equal = 1;
	i = 0;
	j = 0;
	copy = malloc(sizeof(char *) * ft_strlen(str) + 3);
	if (copy == NULL)
		return NULL;
	while (str[i])
	{
		copy[j] = str[i];
		if (str[i] == '=' && first_equal == 1)
		{
			copy[++j] = '"';
			first_equal = 0;	
		}	
		i++;
		j++;
	}
	copy[j] = '"';
	copy[j+1] = 0;
	return (copy);
}

char	**ft_strarrcpy_env(char **array)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (ft_strarrsize(array) + 1));
	i = 0;
	while (array[i])
	{
		copy[i] = ft_strdup_env(array[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}