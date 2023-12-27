/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:47:40 by facu              #+#    #+#             */
/*   Updated: 2023/12/26 16:12:02 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Handles the execution of an exec node. If the command is a builtin, runs
	the builtin and exits, otherwise, runs the command in a child process. */
void	run_exec(t_node *node, int *status, t_shell *shell)
{
	if (is_builtin(node))
	{
		run_builtin(node, shell);
		exit(g_exit_status);
	}
	else
		run_external(node, status, shell);
}

/* Handles the execution of a redirection node. Closes the file descriptor
	and opens the redirection file. */
void	run_redir(t_node *node, t_shell *shell)
{
	t_redirnode	*rnode;

	rnode = (t_redirnode *)node;
	close(rnode->fd);
	if (open_1(rnode->file, rnode->mode) < 0)
		exit(1);
	run_cmd(rnode->node, shell);
}

/* Handles the execution of a heredoc node. Duplicates the file descriptor
	of the heredoc file to stdin. */
void	run_heredoc(t_node *node, t_shell *shell)
{
	t_heredocnode	*hnode;

	hnode = (t_heredocnode *)node;
	if (dup2_1(hnode->fd, STDIN_FILENO) < 0)
		exit(errno);
	close(hnode->fd);
	run_cmd(((t_heredocnode *)node)->execnode, shell);
}

/* Handles the execution of a pipe node. Creates a pipe, forks two child
	processes. Closes the pipe and waits for the child processes to finish. */
void	run_pipe(t_node *node, int *status, t_shell *shell)
{
	t_pipenode	*pnode;
	int			p[2];
	int			left_side_process;
	int			right_side_process;

	pnode = (t_pipenode *)node;
	if (pipe_1(p) < 0)
		exit(EXIT_FAILURE);
	left_side_process = fork_1();
	if (left_side_process < 0)
		exit(errno);
	if (left_side_process == 0)
		return (handle_child_process(p, STDOUT_FILENO, pnode->left, shell));
	right_side_process = fork_1();
	if (right_side_process < 0)
		exit(errno);
	if (right_side_process == 0)
		return (handle_child_process(p, STDIN_FILENO, pnode->right, shell));
	if (close_pipe(p) < 0)
		exit(errno);
	waitpid(left_side_process, NULL, 0);
	waitpid(right_side_process, status, 0);
}

/* Starts the execution. Executes the command tree and 
	sets the exit status to the status of the last command */
void	run_cmd(t_node *node, t_shell *shell)
{
	int	status;

	status = 0;
	if (node == 0)
		return ;
	set_signal_handling(2);
	if (node->type == EXEC)
		run_exec(node, &status, shell);
	else if (node->type == REDIR)
		run_redir(node, shell);
	else if (node->type == HEREDOC)
		run_heredoc(node, shell);
	else if (node->type == PIPE)
		run_pipe(node, &status, shell);
	update_exit_status(status);
	exit(g_exit_status);
}
