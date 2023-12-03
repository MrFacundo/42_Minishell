/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/03 15:48:08 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void	run_node(t_node *node, t_shell *shell)
{
	int	status;

	if (is_builtin(node, 0))
		run_builtin(node, shell);
	else if (fork_1() == 0)
		run_cmd(node, shell);
	else
	{
		set_signal_handling(2);
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_node	*node;
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.parsing_error = 0;
	shell.env = initialize_env(envp);
	while (prompt(&buf, 0) >= 0)
	{
		if (!buf[0])
			continue ;
		add_history(buf);
		node = parse_cmd(buf, &shell);
		if (shell.parsing_error == 0)
			run_node(node, &shell);
		free_tree(node);
		free(buf);
	}
	ft_strarrfree(shell.env);
	return (0);
}
