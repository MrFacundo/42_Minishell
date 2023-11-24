/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:43:48 by facu              #+#    #+#             */
/*   Updated: 2023/11/24 16:49:17 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strarrfind(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
		if (ft_strcmp(array[i++], str) == 0)
			return (1);
	return (0);
}

int	has_alphabetic_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (ft_isalpha(str[i++]))
			return (1);
	return (0);
}
