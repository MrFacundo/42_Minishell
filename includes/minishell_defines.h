/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:47:22 by facu              #+#    #+#             */
/*   Updated: 2023/12/17 23:30:07 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h> 
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>

# define MAXARGS 100
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define HEREDOC 4

# define TOKEN_ERROR 1
# define NO_EXECUTABLE 2

# define WHITESPACE " \t\r\n\v"

typedef struct s_node
{
	int			type;
}				t_node;

typedef struct s_execnode
{
	int			type;
	char		*av[MAXARGS];
	int			ac;
}				t_execnode;

typedef struct s_redirnode
{
	int			type;
	t_node		*node;
	char		*file;
	int			mode;
	int			fd;
}				t_redirnode;

typedef struct s_heredocnode
{
	int			type;
	t_node		*execnode;
	int			fd;
}				t_heredocnode;

typedef struct s_pipenode
{
	int			type;
	t_node		*left;
	t_node		*right;
}				t_pipenode;

typedef struct s_shell
{
	char		**env;
	int			parsing_status;
}	t_shell;

typedef void	(*t_signal_handler)(int);

extern int		g_exit_status;

#endif