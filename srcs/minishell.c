/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/25 21:56:11 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_builtin(t_node *node)
{
	int		is_builtin;
	t_execnode	*enode;

	is_builtin = 0;
	if (node->type != EXEC)
		return (0);
	enode = (t_execnode *)node;
	if (enode->av[0] == 0)
		return (0);
	if (ft_strcmp(enode->av[0], "cd") == 0
		|| ft_strcmp(enode->av[0], "echo") == 0
		|| ft_strcmp(enode->av[0], "exit") == 0
		|| ft_strcmp(enode->av[0], "export") == 0
		|| ft_strcmp(enode->av[0], "pwd") == 0
		|| ft_strcmp(enode->av[0], "unset") == 0)
		is_builtin = 1;
	return (is_builtin);
}

void	run_exit(char **av)
{
	int	exit_code;

	exit_code = 0;
	if (av[1])
		exit_code = ft_atoi(av[1]);
	exit(exit_code);
}

void	run_builtin(t_node *node)
{
	t_execnode	*enode;

	enode = (t_execnode *)node;
	if (ft_strcmp(enode->av[0], "exit") == 0)
		run_exit(enode->av);
	// else if (ft_strcmp(enode->av[0], "echo") == 0)
	// 	run_echo(enode->av);
	// else if (ft_strcmp(enode->av[0], "exit") == 0)
	// 	run_cd(enode->av);
	// else if (ft_strcmp(enode->av[0], "export") == 0)
	// 	run_export(enode->av);
	// else if (ft_strcmp(enode->av[0], "pwd") == 0)
	// 	run_pwd(enode->av);
	// else if (ft_strcmp(enode->av[0], "unset") == 0)
	// 	run_unset(enode->av);
}

int	main(void)
{
	char *buf;

  // TODO: Loop that ensures three file descriptors are open
	while (getcmd(&buf) >= 0) // Main loop
	{
		t_node *node;

		if (*buf)
			add_history(buf);
		node = parsecmd(buf);
		if (is_builtin(node))
			run_builtin(node);
		else
			if (fork1() == 0)
				runcmd(node);
		wait(0);
	}
	return (0);
}

int	getcmd(char **buf)
{
	*buf = readline("ms$ ");
	if (*buf == 0) // Ctrl+D was pressed (EOF)
		return (-1);
	return (0);
}

// Returns a character representing the token type, updates the pointers received as arguments
int	gettoken(char **ptr_to_cmd, char **ptr_to_token, char **end_of_token)
{
	char	*p;
	int		ret;
	char	whitespace[] = " \t\r\n\v";
	char  	symbols_and_whitespace[] = " \t\r\n\v<|>&;()";
	
	p = *ptr_to_cmd;
	p += ft_strspn(p, whitespace);
	if (ptr_to_token)
		*ptr_to_token = p;
	ret = *p;
	switch (*p)
	{
	case 0:
		break ;
	case '|':
	case '<':
		p++;
		break ;
	case '>':
		p++;
		if (*p++ == '>')
			ret = '+';
		break ;
	default:
		ret = 'a';
		p += ft_strcspn(p, symbols_and_whitespace);
		break ;
	}
	if (end_of_token)
		*end_of_token = p;
	p += ft_strspn(p, whitespace);
	*ptr_to_cmd = p;
	printf("//token: %c\n", ret);
	return (ret);
}
 