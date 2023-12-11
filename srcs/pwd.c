/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:18 by facu              #+#    #+#             */
/*   Updated: 2023/12/11 17:28:24 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_pwd()
{
	char	s[PATH_MAX];

	getcwd(s, PATH_MAX);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
	g_exit_status = EXIT_SUCCESS;
}