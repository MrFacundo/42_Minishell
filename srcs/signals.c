/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:21:36 by facu              #+#    #+#             */
/*   Updated: 2023/12/13 01:48:01 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* prints a newline and the prompt when a signal is received */
void	sig_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

/* sets the signal handling for different contexts:
	0: the main process running the shell
	1: processes running external commands
	2: procecess waiting for a command to finish
 */
void	set_signal_handling(int option)
{
	t_signal_handler(*handlers)[3] = malloc(sizeof(t_signal_handler[3]) * 3);
	if (handlers == 0)
		return (print_error(1, "malloc", strerror(errno)));
	handlers[0][0] = sig_handler;
	handlers[0][1] = SIG_IGN;
	handlers[0][2] = SIG_IGN;
	handlers[1][0] = SIG_DFL;
	handlers[1][1] = SIG_DFL;
	handlers[1][2] = SIG_DFL;
	handlers[2][0] = SIG_IGN;
	handlers[2][1] = SIG_IGN;
	handlers[2][2] = SIG_IGN;
	rl_catch_signals = 0;
	if (signal(SIGINT, handlers[option][0]) == SIG_ERR
		|| signal(SIGQUIT, handlers[option][1]) == SIG_ERR
		|| signal(SIGTSTP, handlers[option][2]) == SIG_ERR)
		print_error(2, "signal", strerror(errno));
	free(handlers);
}
