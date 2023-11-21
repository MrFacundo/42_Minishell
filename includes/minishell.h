/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/21 01:35:31 by facu             ###   ########.fr       */
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
# include <signal.h>
#include <termios.h>



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

typedef void	(*t_signal_handler)(int);

extern t_shell	g_shell;

// builtins.c
int		is_builtin(t_node *node, int nested_context);
void	run_builtin(t_node *node);
void	run_exit(char **av);
void	run_echo(char **av);

// builtins_utils.c
int		is_builtin_helper(const char *command, const char *commands[]);
int		has_alphabetic_chars(char *str);

// constructors.c
t_node	*execnode(void);
t_node	*redircmd(t_node *execnode, char *file, char *efile, int mode, int fd);
t_node	*pipenode(t_node *left, t_node *right);

// debug.c
void	print_token(int token);

// env.c
void	initialize_env(t_shell *g_shell, char **envp);
char	*ft_get_env(char *key, char **env);
void	update_env(char *key_value);

// env_utils.c
char	*extract_key(char *key_value);
char	*extract_value(char *key_value);
int		key_matches(char *key, char *env);
void	update_key(char *key, char *value, int i);
void	add_key_to_env(char *key, char *value, int i);

// exec.c
void	runcmd(t_node *node);

// exec_utils.c
void	handle_file_not_found(char *path);
void	handle_permission_denied(char *path);
void	handle_default_error();
void	handle_directory();

// expansion.c
void	expand_exit_status(char **ptr, char **ptr_to_token, char **end_of_token);
void    expand_variable(char **ptr, char **ptr_to_token, char **end_of_token);

// minishell.c
int		getcmd(char **buf);

// parse.c
t_node	*parsecmd(char *cmd);
t_node	*parsepipe(char **pointer_to_cmd);
t_node	*parseredirs(t_node *node, char **pointer_to_cmd);
t_node	*parseexec(char **pointer_to_cmd);

// signals.c
void	sig_handler(int sig);
void	set_signal_handling(int executing_external);

// tokenizer.c
int get_token(char **ptr_to_cmd, char **ptr_to_token, char **end_of_token);

// utils.c
t_node	*nul_terminate(t_node *node);
int		peek(char **pointer_to_cmd, char *tokens);
void	ft_strarrfree(char **array);
void	print_error(int n, ...);
int		fork_1(void);
int		open_1(char *file, int mode);
int		pipe_1(int *p);
char	**ft_strarrcpy(char **array);

#endif