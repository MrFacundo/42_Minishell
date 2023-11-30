/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:43:48 by facu              #+#    #+#             */
/*   Updated: 2023/11/28 17:52:36 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_alphabetic_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (ft_isalpha(str[i++]))
			return (1);
	return (0);
}
