/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/15 11:20:15 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h> // printf
# include <readline/readline.h> // readline
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h> // execve
# include <sys/wait.h> // wait
# include <fcntl.h> // open O_CREAT|O_WRONLY
# include <sys/stat.h> // S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
# include <errno.h> // errno
# include <stdarg.h> // va_start, va_arg, va_end
#include <sys/stat.h> // stat

#define MAXARGS 10

#define EXEC 1
#define REDIR 2
#define PIPE 3

typedef struct	s_node
{
	int			type;
}				t_node;

typedef struct	s_execnode
{
	int			type;
	char		*av[MAXARGS];
	char		*eav[MAXARGS];
}				t_execnode;

typedef struct s_redirnode
{
	int			type;
	t_node		*execnode;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}				t_redirnode;

typedef struct s_pipenode
{
	int			type;
	t_node		*left;
	t_node		*right;
}				t_pipenode;

typedef struct s_shell
{
	char		**env;
	int			exit_code;
}	t_shell;

extern t_shell	g_shell;

// minishell.c
int		getcmd(char **buf);

// constructors.c
t_node	*execnode(void);
t_node	*redircmd(t_node *execnode, char *file, char *efile, int mode, int fd);
t_node	*pipenode(t_node *left, t_node *right);

// debug.c
void	print_token(int token);

// env.c
void	initialize_env(t_shell *g_shell, char **envp);
char	*ft_get_env(char *key, char **env);

// exec.c
void	runcmd(t_node *node);

// exec_utils.c
void	handle_file_not_found(char *path);
void	handle_permission_denied(char *path);
void	handle_default_error();
void	handle_directory();

// parse.c
t_node	*parsecmd(char *cmd);
t_node	*parsepipe(char **pointer_to_cmd);
t_node	*parseredirs(t_node *node, char **pointer_to_cmd);
t_node	*parseexec(char **pointer_to_cmd);


// tokenizer.c
int get_token(char **ptr_to_cmd, char **ptr_to_token, char **end_of_token);

// utils.c
t_node	*nul_terminate(t_node *node);
int		peek(char **pointer_to_cmd, char *tokens);
void	free_array(char **array);
void	print_error(int n, ...);
int		fork_1(void);
int		open_1(char *file, int mode);
int		pipe_1(int *p);

#endif