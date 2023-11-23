/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:21:36 by facu              #+#    #+#             */
/*   Updated: 2023/11/21 16:39:54 by ftroiter         ###   ########.fr       */
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
	g_shell.exit_code = 130;
}

/* sets the signal handling for different contexts:
	0: for the process running the shell
	1: for the process running an external command
	2: for procecess waiting for a command to finish
 */
void	set_signal_handling(int option)
{
	t_signal_handler handlers[][3] = {
		{sig_handler, SIG_IGN, SIG_IGN},
		{SIG_DFL, SIG_DFL, SIG_DFL},
		{SIG_IGN, SIG_IGN, SIG_IGN}
	};
	rl_catch_signals = 0;
	if (signal(SIGINT, handlers[option][0]) == SIG_ERR ||
			signal(SIGQUIT, handlers[option][1]) == SIG_ERR ||
			signal(SIGTSTP, handlers[option][2]) == SIG_ERR)
				return (print_error(2, "signal", strerror(errno)));
}