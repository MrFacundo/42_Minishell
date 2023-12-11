/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:18:56 by facu              #+#    #+#             */
/*   Updated: 2023/12/11 17:16:10 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_file_not_found(char *path)
{
	if (ft_strchr(path, '/') != 0)
		print_error(1, strerror(errno));
	else
		print_error(1, "command not found");
	g_exit_status = 127;
	exit(g_exit_status);
}

void	handle_permission_denied(char *path)
{
	if (ft_strchr(path, '/') != 0)
	{
		print_error(1, strerror(errno));
		g_exit_status = 126;
	}
	else
	{
		print_error(1, "command not found");
		g_exit_status = 127;
	}
	exit(g_exit_status);
}

void	handle_directory()
{
	print_error(1, strerror(EISDIR));
	g_exit_status = 126;
	exit(g_exit_status);

}
void	handle_default_error()
{
	print_error(1, strerror(errno));
	g_exit_status = errno;
	exit(g_exit_status);
}