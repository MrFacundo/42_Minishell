/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/22 15:43:44 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

/* If the command is belongs to a set of builtins, runs the builtin in the main
	process, otherwise, runs the command in a child process.
	Handles signals and waits for the child process to finish */
void	run_node(t_node *node, t_shell *shell)
{
	int	status;

	if (is_builtin(node))
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

/* Initializes the shell environment, runs the prompt loop,
	frees allocated memory */
int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_node	*node;
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = initialize_env(envp);
	if (!shell.env)
		return (1);
	while (prompt(&buf, 0) >= 0)
	{
		if (!buf[0])
			continue ;
		add_history(buf);
		node = parse_cmd(buf, &shell);
		if (shell.parsing_status == 0)
			run_node(node, &shell);
		free_tree(node);
		free(buf);
	}
	ft_strarrfree(shell.env);
	return (0);
}
