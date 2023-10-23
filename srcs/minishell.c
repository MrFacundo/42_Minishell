/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/22 21:16:17 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *buf;

  // TODO: Loop that ensures three file descriptors are open
  // Main loop
	while (getcmd(&buf) >= 0)
	{
		// TODO: before forking, check for builtins
		if (fork1() == 0)
			runcmd(parsecmd(buf));
		wait(0);
	}
	return (0);
}

int	getcmd(char **buf)
{
	rl_initialize(); // not sure if this is needed
	*buf = readline("ms$ ");
	if (*buf == 0) // Ctrl+D was pressed (EOF)
		return (-1);
	return (0);
}

// Recursive parse function: cmd
t_node	*parsecmd(char *cmd)
{
	t_node	*node;

	node = parseexec(&cmd);
	nulterminate(node);
	return (node);
}

// Recursive parse function: exec
t_node	*parseexec(char **pointer_to_cmd)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*pointer_to_token, *end_of_token;
	int			token, ac;
	
	ac = 0;
	ret = execnode();
	exec_node = (t_execnode *)ret;
	while (!peek(pointer_to_cmd, "|)&;"))
	{
		token = gettoken(pointer_to_cmd, &pointer_to_token, &end_of_token);
		if (token == 0)
			break ;
		if (token != 'a')
			{}; // TODO: syntax error
		exec_node->av[ac] = pointer_to_token;
		exec_node->eav[ac] = end_of_token;
		ac++;
		if (ac >= MAXARGS)
			{}; // TODO: max args error
	}
	exec_node->av[ac] = 0;
	exec_node->eav[ac] = 0;
	return (ret);
}

// Returns a character representing the token type, updates the pointers received as arguments
int	gettoken(char **pointer_to_cmd, char **pointer_to_token, char **end_of_token)
{
	char	*s;
	int		ret;
	char	whitespace[] = " \t\r\n\v";
	char  	symbols_and_whitespace[] = " \t\r\n\v<|>&;()";
	
	s = *pointer_to_cmd;
	s += ft_strspn(s, whitespace);
	if (pointer_to_token)
		*pointer_to_token = s;
	ret = *s;
	switch (*s)
	{
	case 0:
		break ;
	default:
		ret = 'a';
		s += ft_strcspn(s, symbols_and_whitespace);
		break ;
	}
	if (end_of_token)
		*end_of_token = s;
	s += ft_strspn(s, whitespace);
	*pointer_to_cmd = s;
	return (ret);
}
