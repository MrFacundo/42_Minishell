/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/24 17:20:48 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell			g_shell;


void	free_tree(t_node *node)
{
	if (node == 0)
		return ;
	if (node->type == EXEC)
		free(node);
	else if (node->type == REDIR)
	{
		free_tree(((t_redirnode *)node)->execnode);
		free(node);
	}
	else if (node->type == PIPE)
	{
		free_tree(((t_pipenode *)node)->left);
		free_tree(((t_pipenode *)node)->right);
		free(node);
	}
	else if (node->type == HEREDOC)
	{
		free_tree(((t_heredocnode *)node)->execnode);
		free(node);
	}
}


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
	while (prompt(&buf, 0) >= 0)
	{
		add_history(buf);
		node = parsecmd(buf);
		if (node == 0)
			continue ;
		if (is_builtin(node, 0))
			run_builtin(node);
		else
		{
			if (fork_1() == 0)
				runcmd(node);
			set_signal_handling(2);
			wait(&status);
			g_shell.exit_code = WEXITSTATUS(status);
		}
		free_tree(node);
	}
	ft_strarrfree(g_shell.env);
	return (0);
}
