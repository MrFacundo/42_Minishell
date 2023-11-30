/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/30 13:45:58 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*parsecmd(char *cmd)
{
	t_node	*node;

	node = parsepipe(&cmd);
	return (node);
}

t_node	*parsepipe(char **ptr_to_cmd)
{
	t_node	*left;

	left = parseexec(ptr_to_cmd);
	if (peek(ptr_to_cmd, "|"))
	{
		get_token(ptr_to_cmd, 0, 0);
		if (**ptr_to_cmd == '\0' || peek(ptr_to_cmd, "|()&;<>"))
			return (print_error(1, "parse error near pipe"), NULL);
		return (pipenode(left, parsepipe(ptr_to_cmd)));
	}
	return (left);
}

t_node	*parseredirs(t_node *node, char **ptr_to_cmd)
{
	int		token;
	int		file_token;
	char 	*ptr_to_token;
	char 	*end_of_token;

	while (peek(ptr_to_cmd, "<>"))
	{
		token = get_token(ptr_to_cmd, 0, 0);
		file_token = get_token(ptr_to_cmd, &ptr_to_token, &end_of_token);
		if (file_token != 'a' && file_token != '$')
			return (print_error(1, "parse error near redirection"), NULL);
		if (file_token == '$')
			end_of_token = 0;
		if (token == '<')
			node = redircmd(node, ptr_to_token, end_of_token, O_RDONLY, 0);
		else if (token == '>')
			node = redircmd(node, ptr_to_token, end_of_token, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '+')
			node = redircmd(node, ptr_to_token, end_of_token, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token == '-')
			node = heredoccmd(node, ptr_to_token, end_of_token);
	}
	return (node);
}

t_node	*parseexec(char **ptr_to_cmd)
{
	t_node *ret;
	t_execnode *exec_node;
	char *ptr_to_token, *end_of_token;
	int token, ac;

	ac = 0;
	ret = execnode();
	exec_node = (t_execnode *)ret;
	// ret = parseredirs(ret, ptr_to_cmd); not sure about this line
	while (!peek(ptr_to_cmd, "<>|()&;"))
	{
		token = get_token(ptr_to_cmd, &ptr_to_token, &end_of_token);
		if (token == 0)
			break ;
		if (token == 'e')
			return (0);
		if (token == '$')
			exec_node->av[ac] = ptr_to_token;
		else
			exec_node->av[ac] = ft_substr(ptr_to_token, 0, end_of_token - ptr_to_token);
		ac++;
		if (ac >= MAXARGS)
			return (print_error(1, "too many args"), NULL);
		ret = parseredirs(ret, ptr_to_cmd);
	}
	exec_node->av[ac] = 0;
	return (ret);
}