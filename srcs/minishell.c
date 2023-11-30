/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/30 18:04:46 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

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

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_node	*node;

	(void)argc;
	(void)argv;
	initialize_env(&g_shell, envp);
	g_shell.exit_status = 0;
	g_shell.parsing_error = 0;
	while (prompt(&buf, 0) >= 0)
	{
		add_history(buf);
		node = parsecmd(buf);
		if (g_shell.parsing_error == 0)
			run_node(node);
		free_tree(node);
		free(buf);
	}
	ft_strarrfree(g_shell.env);
	return (0);
}
