/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:33 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_argumet(char *arg, t_shell *shell)
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
	else
	{
		print_error(2, "unset", "not a valid identifier");
		g_exit_status = EXIT_FAILURE;
	}
}

void	run_unset(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	while (av[i])
	{
		unset_argumet(av[i], shell);
		i++;
	}
}
