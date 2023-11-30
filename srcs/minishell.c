/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/30 18:56:03 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;
extern char **environ;

void	run_node(t_node *node)
{
	int	status;

	if (is_builtin(node, 0))
		run_builtin(node);
	else if (fork_1() == 0)
		run_cmd(node);
	else
	{
		set_signal_handling(2);
		wait(&status);
		g_shell.exit_status = WEXITSTATUS(status);
	}
}

int	main(void)
{
	char	*buf;
	t_node	*node;

	initialize_env(&g_shell, environ);
	g_shell.exit_status = EXIT_SUCCESS;
	g_shell.parsing_error = 0;
	while (prompt(&buf, 0) >= 0)
	{
		add_history(buf);
		node = parse_cmd(buf);
		if (g_shell.parsing_error == 0)
			run_node(node);
		free_tree(node);
		free(buf);
	}
	ft_strarrfree(g_shell.env);
	return (0);
}
