/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:40 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/22 21:33:15 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h> // printf
# include <readline/readline.h> // readline
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h> // execve
#include <sys/wait.h> // wait

#define MAXARGS 10

#define EXEC 1

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

// minishell.c
int		getcmd(char **buf);
t_node	*parsecmd(char *cmd);
t_node	*parseexec(char **pointer_to_cmd);
int		gettoken(char **pointer_to_cmd, char **pointer_to_token, char **end_of_token);

// constructors.c
t_node	*execnode(void);

// exec.c
void	runcmd(t_node *node);

// utils.c
void	panic(char *s);
int		fork1(void);
t_node	*nulterminate(t_node *node);
int		peek(char **pointer_to_cmd, char *tokens);



#endif