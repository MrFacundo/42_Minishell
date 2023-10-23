/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/23 19:01:36 by ftroiter         ###   ########.fr       */
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

t_node	*parseredirs(t_node *node, char **pointer_to_cmd)
{
	int	token;

	char	*ptr_to_token, *end_of_token;
	while (peek(pointer_to_cmd, "<>"))
	{
		token = gettoken(pointer_to_cmd, 0, 0);
		if (gettoken(pointer_to_cmd, &ptr_to_token, &end_of_token) != 'a')
			panic("missing file for redirection");
		switch (token)
		{
		case '<':
			node = redircmd(node, ptr_to_token, end_of_token, O_RDONLY, 0);
			break ;
		case '>':
			node = redircmd(node, ptr_to_token, end_of_token, O_WRONLY | O_CREAT | O_TRUNC, 1);
			break ;
		case '+': // >>	
			node = redircmd(node, ptr_to_token, end_of_token, O_WRONLY | O_CREAT | O_APPEND, 1);
			break ;
		}
	}
	return (node);
}

// Recursive parse function: exec
t_node	*parseexec(char **pointer_to_cmd)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*ptr_to_token, *end_of_token;
	int			token, ac;
	
	ac = 0;
	ret = execnode();
	exec_node = (t_execnode *)ret;
	// ret = parseredirs(ret, pointer_to_cmd); not sure what this line does
	while (!peek(pointer_to_cmd, "|)&;"))
	{
		token = gettoken(pointer_to_cmd, &ptr_to_token, &end_of_token);
		if (token == 0)
			break ;
		if (token != 'a')
			panic("syntax");
		exec_node->av[ac] = ptr_to_token;
		exec_node->eav[ac] = end_of_token;
		ac++;
		if (ac >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, pointer_to_cmd);
	}
	exec_node->av[ac] = 0;
	exec_node->eav[ac] = 0;
	return (ret);
}

// Returns a character representing the token type, updates the pointers received as arguments
int	gettoken(char **pointer_to_cmd, char **ptr_to_token, char **end_of_token)
{
	char	*p;
	int		ret;
	char	whitespace[] = " \t\r\n\v";
	char  	symbols_and_whitespace[] = " \t\r\n\v<|>&;()";
	
	p = *pointer_to_cmd;
	p += ft_strspn(p, whitespace);
	if (ptr_to_token)
		*ptr_to_token = p;
	ret = *p;
	switch (*p)
	{
	case 0:
		break ;
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
	*pointer_to_cmd = p;
	return (ret);
}
 