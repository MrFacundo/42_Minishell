/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:43:48 by facu              #+#    #+#             */
/*   Updated: 2023/11/18 20:44:14 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_helper(const char *command, const char *builtin_commands[])
{
	int	i;

	i = 0;
	while (builtin_commands[i] != 0)
		if (!ft_strcmp(command, builtin_commands[i++]))
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