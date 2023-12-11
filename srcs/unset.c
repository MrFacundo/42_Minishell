/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:33 by facu              #+#    #+#             */
/*   Updated: 2023/12/11 17:28:48 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_unset(char **av, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (is_valid_identifier(av[i]))
		{
			j = 0;
			while(shell->env[j])
			{
				if (key_matches(av[i], shell->env[j]))
				{
					unset_env(av[i], shell);
					break ;
				}
				j++;
			}
		}
		else
		{
			print_error(2, "unset", "not a valid identifier");
			g_exit_status = EXIT_FAILURE;
		}
		i++;
	}
}