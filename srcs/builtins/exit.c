/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:29:20 by facu              #+#    #+#             */
/*   Updated: 2023/12/21 17:44:57 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_exit(char **av)
{
	long long	arg_value;

	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	else if (av[1])
	{
		arg_value = ft_atoll(av[1]);
		if (ft_strlen(av[1]) > 19
			|| has_alphabetic_chars(av[1])
			|| !(arg_value >= -9223372036854775807 \
			&& arg_value <= 9223372036854775807))
		{
			print_error(2, "exit", "numeric argument required");
			g_exit_status = 2;
		}
		else
			g_exit_status = (int)arg_value;
	}
	exit(g_exit_status);
}
