/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:21:36 by facu              #+#    #+#             */
/*   Updated: 2023/12/01 15:15:34 by facu             ###   ########.fr       */
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
	g_exit_status= 130;
}

/* sets the signal handling for different contexts:
	0: the main process running the shell
	1: processes running an external commands
	2: procecess waiting for a command to finish
 */
void	set_signal_handling(int option)
{
	t_signal_handler handlers[][3] = {
		{sig_handler, SIG_IGN, SIG_IGN},
		{SIG_DFL, SIG_DFL, SIG_DFL},
		{SIG_IGN, SIG_IGN, SIG_IGN},
	};
	rl_catch_signals = 0;
	if (signal(SIGINT, handlers[option][0]) == SIG_ERR ||
			signal(SIGQUIT, handlers[option][1]) == SIG_ERR ||
			signal(SIGTSTP, handlers[option][2]) == SIG_ERR)
				return (print_error(2, "signal", strerror(errno)));
}
