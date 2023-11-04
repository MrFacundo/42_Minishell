/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/03 16:39:30 by facu             ###   ########.fr       */
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
}	t_shell;

extern t_shell	g_shell;

// minishell.c
int		getcmd(char **buf);
int		gettoken(char **pointer_to_cmd, char **ptr_to_token, char **end_of_token);
int		gettoken(char **pointer_to_cmd, char **pointer_to_token, char **end_of_token);

// constructors.c
t_node	*execnode(void);
t_node	*redircmd(t_node *execnode, char *file, char *efile, int mode, int fd);
t_node	*pipenode(t_node *left, t_node *right);

// env
char	*ft_get_env(char *key, char **env);

// exec.c
void	runcmd(t_node *node);

// parse.c
t_node	*parsecmd(char *cmd);
t_node	*parsepipe(char **pointer_to_cmd);
t_node	*parseredirs(t_node *node, char **pointer_to_cmd);
t_node	*parseexec(char **pointer_to_cmd);

// utils.c
void	panic(char *s);
int		fork1(void);
t_node	*nulterminate(t_node *node);
int		peek(char **pointer_to_cmd, char *tokens);
void	free_array(char **array);
void	print_error(char *error);
int		open_1(char *file, int mode);


#endif