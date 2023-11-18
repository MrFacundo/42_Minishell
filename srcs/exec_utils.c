/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:18:56 by facu              #+#    #+#             */
/*   Updated: 2023/11/18 20:47:42 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_file_not_found(char *path)
{
	if (ft_strchr(path, '/') != 0)
		print_error(1, strerror(errno));
	else
		print_error(1, "command not found");
	g_shell.exit_code = 127;
	exit(g_shell.exit_code);
}

void	handle_permission_denied(char *path)
{
	if (ft_strchr(path, '/') != 0)
	{
		print_error(1, strerror(errno));
		g_shell.exit_code = 126;
	}
	else
	{
		print_error(1, "command not found");
		g_shell.exit_code = 127;
	}
	exit(g_shell.exit_code);
}

void	handle_directory()
{
	print_error(1, strerror(EISDIR));
	g_shell.exit_code = 126;
	exit(g_shell.exit_code);

}
void	handle_default_error()
{
	print_error(1, strerror(errno));
	g_shell.exit_code = errno;
	exit(g_shell.exit_code);
}