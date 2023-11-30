#include "../includes/minishell.h"

void	run_exec(t_node *node, int *status)
{
	t_execnode	*enode;
	char		*path;

	enode = (t_execnode *)node;
	if (enode->av[0] == 0)
		exit(0);
	if (ft_strchr(enode->av[0], '/') == 0)
		path = find_path(enode->av[0]);
	else
		path = ft_strdup(enode->av[0]);
	if (fork_1() == 0)
		execute_command(path, enode->av);
	wait(status);
	free(path);
}

void	run_redir(t_node *node)
{
	t_redirnode	*rnode;

	rnode = (t_redirnode *)node;
	close(rnode->fd);
	if (open_1(rnode->file, rnode->mode) < 0)
		exit(ENOENT);
	run_cmd(rnode->execnode);
}

void	run_heredoc(t_node *node)
{
	t_heredocnode	*hnode;

	hnode = (t_heredocnode *)node;
	if (dup2_1(hnode->fd, 0) < 0)
		exit(errno);
	close(hnode->fd);
	run_cmd(((t_heredocnode *)node)->execnode);
}

void	run_pipe(t_node *node, int *status)
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
		return (handle_child_process(p, 1, pnode->left));
	right_side_process = fork_1();
	if (right_side_process < 0)
		exit(errno);
	if (right_side_process == 0)
		return (handle_child_process(p, 0, pnode->right));
	if (close_pipe(p) < 0)
		exit(errno);
	wait(status);
}

void	run_cmd(t_node *node)
{
	int status;

	if (node == 0)
		return ;
	set_signal_handling(2);
	if (node->type == EXEC)
	{
		if (is_builtin(node, 1))
			run_builtin(node);
		else
			run_exec(node, &status);
	}
	else if (node->type == REDIR)
		run_redir(node);
	else if (node->type == HEREDOC)
		run_heredoc(node);
	else if (node->type == PIPE)
		run_pipe(node, &status);
	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_shell.exit_status = WTERMSIG(status) + 128;
	exit(g_shell.exit_status);
}