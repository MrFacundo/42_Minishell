/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:29:20 by facu              #+#    #+#             */
/*   Updated: 2023/12/19 21:40:38 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	ret;
	int			digit;

	sign = 1;
	ret = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
		sign = (*str++ == '-') ? -1 : 1;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		ret = ret * 10 + sign * digit;
		++str;
	}
	return (ret);
}

void run_exit(char **av)
{
	long long	arg_value;

	if (av[2])
	{
		print_error(2, "exit", "too many arguments");
		g_exit_status = EXIT_FAILURE;
		return;
	}
	else if (av[1])
	{
		arg_value = ft_atoll(av[1]);
		if (has_alphabetic_chars(av[1]) || !(arg_value >= -9223372036854775807 && arg_value <= 9223372036854775807))
		{
			print_error(2, "exit", "numeric argument required");
			g_exit_status = 2;
		}
		else
			g_exit_status = (int)arg_value;
	}
	exit(g_exit_status);
}
