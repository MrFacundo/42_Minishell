/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:29:20 by facu              #+#    #+#             */
/*   Updated: 2023/12/11 17:29:35 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_exit(char **av)
{
	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_exit_status = EXIT_FAILURE;
	}
	else if (has_alphabetic_chars(av[1]))
	{
		print_error(2, "exit", "numeric argument required");
		g_exit_status = 2;
	}
	else if (av[1])
		g_exit_status = ft_atoi(av[1]);
	exit(g_exit_status);
}