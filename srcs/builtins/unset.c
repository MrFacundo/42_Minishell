/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:33 by facu              #+#    #+#             */
/*   Updated: 2023/12/16 18:44:11 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_argument(char *arg, t_shell *shell)
{
	int	j;

	if (is_valid_identifier(arg))
	{
		j = 0;
		while (shell->env[j])
		{
			if (key_matches(arg, shell->env[j]))
			{
				unset_env(arg, shell);
				return ;
			}
			j++;
		}
	}
}

void	run_unset(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	while (av[i])
	{
		unset_argument(av[i], shell);
		i++;
	}
	g_exit_status = EXIT_SUCCESS;
}
