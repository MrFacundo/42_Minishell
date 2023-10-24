/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/24 17:07:52 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *buf;

  // TODO: Loop that ensures three file descriptors are open
	while (getcmd(&buf) >= 0) // Main loop
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
	*buf = readline("ms$ ");
	if (*buf == 0) // Ctrl+D was pressed (EOF)
		return (-1);
	return (0);
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
	*pointer_to_cmd = p;
	return (ret);
}
 