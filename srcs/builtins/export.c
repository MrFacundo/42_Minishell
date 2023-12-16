/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:27:52 by facu              #+#    #+#             */
/*   Updated: 2023/12/16 18:37:46 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_export(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	g_exit_status = EXIT_SUCCESS;
	if (av[1] == 0)
		print_env(shell->env);
	else
	{
		while (av[i])
		{
			if (!is_valid_identifier(av[i]))
			{
				print_error(3, "export", av[i], "not a valid identifier");
				g_exit_status = EXIT_FAILURE;
			}
			else
				set_env(av[i], shell);
			++i;
		}
	}
}
