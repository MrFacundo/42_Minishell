/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/18 20:33:33 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell			g_shell;

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_node	*node;
	int		status;

	(void)argc;
	(void)argv;
	initialize_env(&g_shell, envp);
	g_shell.exit_code = 0;
	status = 0;
	while (getcmd(&buf) >= 0)
	{
		add_history(buf);
		node = parsecmd(buf);
		if (node == 0)
			continue ;
		if (is_builtin(node, 0))
			run_builtin(node);
		else if (fork_1() == 0)
			runcmd(node);
		set_signal_handling(2);
		wait(&status);
		g_shell.exit_code = WEXITSTATUS(status);
	}
	return (0);
}

int	getcmd(char **buf)
{
	set_signal_handling(0);
	*buf = readline("ms > ");
	if (*buf == 0)
		return (-1);
	return (0);
}
