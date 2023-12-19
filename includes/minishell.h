/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/19 20:28:15 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_defines.h"

// builtins.c
int		is_builtin(t_node *node, int nested_context);
void	run_builtin(t_node *node, t_shell *shell);

// builtins_utils.c
int		ft_strarrfind(char **array, char *str);
int		has_alphabetic_chars(char *str);
void	process_export_args(char **av);

//cd.c

void	run_cd(char **av, t_shell *shell);

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

// echo.c
void	run_echo(char **av);

// env_utils_1.c

int		key_matches(char *key, char *env);
void	update_key(char *key, char *value, int i, t_shell *shell);
void	add_key_to_env(char *key, char *value, t_shell *shell);
int		is_valid_identifier(const char *str);

// env_utils_2.c
char	*extract_key(char *key_value);
char	*extract_value(char *key_value);
int		find_key_index(char *key, t_shell *shell);

// exec_utils.c
void	handle_child_process(int *pipe, int direction, t_node *node,
			t_shell *shell);
void	execute_command(char *path, char **av, t_shell *shell);
void	update_exit_status(int status);
void	run_external(t_node *node, int *status, t_shell *shell);

// exec_error_handlung.c
void	handle_file_not_found(char *path);
void	handle_permission_denied(char *path);
void	handle_default_error(void);
void	handle_directory(void);

// exec_path_finding.c
char	*find_path(char *cmd, t_shell *shell);

// execution.c
void	run_cmd(t_node *node, t_shell *shell);

// exit.c
void	run_exit(char **av);

void	expand_variable(char *ptr, char **tkn_ptr, t_shell *shell);

// export.c
void	run_export(char **av, t_shell *shell);

// parse.c
t_node	*parse_cmd(char *cmd, t_shell *shell);
t_node	*parsepipe(char **pointer_to_cmd, t_shell *shell);
t_node	*parseredirs(t_node *node, char **pointer_to_cmd, t_shell *shell);
t_node	*parseexec(char **pointer_to_cmd, t_shell *shell);

// parsing_utils.c
t_node	*handle_parse_error(t_node *ret, const char *error_message,
			t_shell *shell);
t_node	*reverse_redir_nodes_help(t_node *root);
t_node	*parseredirs_help(t_node *node, char **tkn_ptr, int token);

// pwd.c
void	run_pwd(void);

// read.c
int		prompt(char **buf, char *prompt);
int		read_heredoc(char *delimiter);

// signals.c
void	sig_handler(int sig);
void	set_signal_handling(int executing_external);

// token_utils.c
int		calculate_token_length(char *ptr, t_shell *shell, int *has_quotes);

// token_utils_2.c
char	*extract_token(char **ptr, int len, t_shell *shell);

// token_utils_3.c
void	extract_exit_status(char **ptr, char **ret);
void	extract_alpha_variable(char **ptr, char **ret, t_shell *shell);

// tokenizer.c
int		get_token(char **cmd_ptr, char **tkn_ptr, t_shell *shell);

// unset.c
void	run_unset(char **av, t_shell *shell);

// utils.c
int		peek(char **pointer_to_cmd, char *tokens);
void	print_error(int n, ...);
int		fork_1(void);
int		open_1(char *file, int mode);
int		pipe_1(int *p);
int		dup2_1(int oldfd, int newfd);
int		close_pipe(int *p);
void	free_tree(t_node *node);
void	free_strings(char *str, ...);

#endif