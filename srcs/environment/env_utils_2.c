/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:40 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
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
