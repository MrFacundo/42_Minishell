/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/24 17:10:20 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recursive parse function: cmd node
t_node	*parsecmd(char *cmd)
{
	t_node	*node;

	node = parsepipe(&cmd);
	nulterminate(node);
	return (node);
}

// Recursive parse function: pipe node
t_node	*parsepipe(char **pointer_to_cmd)
{
	t_node	*left;

	left = parseexec(pointer_to_cmd);
	if (peek(pointer_to_cmd, "|"))
	{
		gettoken(pointer_to_cmd, 0, 0);
		return (pipenode(left, parsepipe(pointer_to_cmd)));
	}
	return (left);
}

// Recursive parse function: redirection node
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

// Recursive parse function: exec node
t_node	*parseexec(char **pointer_to_cmd)
{
	t_node		*ret;
	t_execnode	*exec_node;
	char		*ptr_to_token, *end_of_token;
	int			token, ac;
	
	ac = 0;
	ret = execnode();
	exec_node = (t_execnode *)ret;
	// ret = parseredirs(ret, pointer_to_cmd); not sure about this line
	while (!peek(pointer_to_cmd, "|)&;"))
	{
		token = gettoken(pointer_to_cmd, &ptr_to_token, &end_of_token);
		printf("token: %c\n", token);
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