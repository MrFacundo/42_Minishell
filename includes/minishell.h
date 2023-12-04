/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/04 13:09:18 by facu             ###   ########.fr       */
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
#define MAXTOKENSIZE 100
#define EXEC 1
#define REDIR 2
#define PIPE 3
#define HEREDOC 4

#define TOKEN_ERROR 1

typedef struct	s_node
{
	int			type;
}				t_node;

typedef struct	s_execnode
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
	int			parsing_error;
}	t_shell;

typedef void	(*t_signal_handler)(int);

extern	int		g_exit_status;

// builtins.c
int		is_builtin(t_node *node, int nested_context);
void	run_builtin(t_node *node, t_shell *shell);

// builtins_utils.c
int		ft_strarrfind(char **array, char *str);
int		has_alphabetic_chars(char *str);
void	process_export_args(char **av);

// constructors.c
t_node	*execnode(void);
t_node	*redircmd(t_node *execnode, char *file, int mode, int fd);
t_node	*pipenode(t_node *left, t_node *right);
t_node	*heredoccmd(t_node *execnode, char *delimiter);

// debug.c
void	print_token(int token);

// env.c
char	**initialize_env(char **envp);
char	*ft_get_env(char *key, char **env);
void	set_env(char *key_value, t_shell *shell);
void	unset_env(char *key, t_shell *shell);
void	print_env(char **env);

// env_utils.c
char	*extract_key(char *key_value);
char	*extract_value(char *key_value);
int		key_matches(char *key, char *env);
void	update_key(char *key, char *value, int i, t_shell *shell);
void	add_key_to_env(char *key, char *value, t_shell *shell);
int		is_valid_identifier(const char *str);

// exec_utils.c
char	*find_path(char *cmd, t_shell *shell);
void	handle_child_process(int *pipe, int direction, t_node *node, t_shell *shell);
void	execute_command(char *path, char **av, t_shell *shell);
void	update_exit_status(int status);
void	run_external(t_node *node, int *status, t_shell *shell);

// exec_error_handlung.c
void	handle_file_not_found(char *path);
void	handle_permission_denied(char *path);
void	handle_default_error();
void	handle_directory();

// execution.c
void	run_cmd(t_node *node, t_shell *shell);

// expansion.c
void    expand_variable(char *ptr, char **tkn_ptr, t_shell *shell);

// parse.c
t_node	*parse_cmd(char *cmd, t_shell *shell);
t_node	*parsepipe(char **pointer_to_cmd, t_shell *shell);
t_node	*parseredirs(t_node *node, char **pointer_to_cmd, t_shell *shell);
t_node	*parseexec(char **pointer_to_cmd, t_shell *shell);

// read.c
int		prompt(char **buf, char *prompt);
int		read_heredoc(char *delimiter);

// signals.c
void	sig_handler(int sig);
void	set_signal_handling(int executing_external);

// token_utils.c
int		calculate_token_length(char *ptr, t_shell *shell);

// token_utils_2.c
char	*extract_token(char **ptr, int len, t_shell *shell);

// token_utils_3.c
void	extract_exit_status(char **ptr, char **ret);
void	extract_alpha_variable(char **ptr, char **ret, t_shell *shell);

// tokenizer.c
int get_token(char **cmd_ptr, char **tkn_ptr, t_shell *shell);

// utils.c
int		peek(char **pointer_to_cmd, char *tokens);
void	print_error(int n, ...);
int		fork_1(void);
int		open_1(char *file, int mode);
int		pipe_1(int *p);
int		dup2_1(int oldfd, int newfd);
int		close_pipe(int *p);
void	free_tree(t_node *node);


#endif