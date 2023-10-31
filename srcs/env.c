/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:41:47 by facu              #+#    #+#             */
/*   Updated: 2023/10/31 19:43:01 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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