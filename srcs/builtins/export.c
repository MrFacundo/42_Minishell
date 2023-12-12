/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:27:52 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_export(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	if (av[1] == 0)
	{
		print_env(shell->env);
		g_exit_status = EXIT_SUCCESS;
	}
	else
	{
		while (av[i])
		{
			if (!is_valid_identifier(av[i]))
			{
				print_error(2, "export", "not a valid identifier");
				g_exit_status = EXIT_FAILURE;
				return ;
			}
			else
				set_env(av[i], shell);
			++i;
		}
		g_exit_status = EXIT_SUCCESS;
	}
}
