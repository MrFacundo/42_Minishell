/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:29:20 by facu              #+#    #+#             */
/*   Updated: 2023/12/26 22:54:12 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int calc_over_long(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 19)
		return 1;
	if (str[0] == '-')
	{
		if (ft_strcmp("9223372036854775808", &str[i]) < 0)
			return 1;
	}
	else
	{
		if (ft_strcmp("9223372036854775807", &str[i]) < 0)
			return 1;
	}
	return 0;
}

void	run_exit(char **av)
{
	long long	arg_value;

	// 	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	else if (av[1])
	{		
		if (has_alphabetic_chars(av[1]) || calc_over_long(av[1]))
		{
			print_error(2, "exit", "numeric argument required");
			g_exit_status = 2;
		}
		else
		{
			arg_value = ft_atoll(av[1]);
			g_exit_status = (int)arg_value;
		}
	}
	exit(g_exit_status);
}
