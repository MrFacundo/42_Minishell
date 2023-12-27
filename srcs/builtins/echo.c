/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:29:49 by facu              #+#    #+#             */
/*   Updated: 2023/12/26 16:23:43 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flagn(const char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	if ((str[i] == '-') && (str[i + 1] != 0))
	{
		i++; 
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	run_echo(char **av)
{
	int	i;
	int	print_newline;
	int	printable;

	i = 1;
	print_newline = 1;
	printable = 0;
	while (av[i])
	{
		if (check_flagn(av[i]) == 1 && printable == 0)
			print_newline = 0;
		else
		{
			printable = 1;
			ft_putstr_fd(av[i], STDOUT_FILENO);
			if (av[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = EXIT_SUCCESS;
}
