/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/21 17:41:27 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

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
void	process_export_args(char **av);

// constructors.c
t_node	*execnode(void);
t_node	*redircmd(t_node *execnode, char *file, char *efile, int mode, int fd);
t_node	*pipenode(t_node *left, t_node *right);

// debug.c
void	print_token(int token);

// env.c
void	initialize_env(t_shell *g_shell, char **envp);
char	*ft_get_env(char *key, char **env);
void	set_env(char *key_value);
void	unset_env(char *key);
void	print_env();

// env_utils.c
char	*extract_key(char *key_value);
char	*extract_value(char *key_value);
int		key_matches(char *key, char *env);
void	update_key(char *key, char *value, int i);
void	add_key_to_env(char *key, char *value);
int		is_valid_identifier(const char *str);

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
void	print_error(int n, ...);
int		fork_1(void);
int		open_1(char *file, int mode);
int		pipe_1(int *p);

#endif