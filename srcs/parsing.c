/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:07:29 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/01 16:03:22 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*parse_cmd(char *cmd, t_shell *shell)
{
	t_node	*node;

	shell->parsing_error = 0;
	node = parsepipe(&cmd, shell);
	if (shell->parsing_error == TOKEN_ERROR)
		g_exit_status = TOKEN_ERROR;
	return (node);
}

t_node	*parsepipe(char **ptr_to_cmd, t_shell *shell)
{
	t_node	*left;

	left = parseexec(ptr_to_cmd, shell);
	if (shell->parsing_error != TOKEN_ERROR && peek(ptr_to_cmd, "|"))
	{
		get_token(ptr_to_cmd, 0, 0, shell);
		if (**ptr_to_cmd == '\0' || peek(ptr_to_cmd, "|()&;<>"))
		{
			shell->parsing_error = TOKEN_ERROR;
			print_error(1, "Parse error near pipe");
			return (0);
		}
		return (pipenode(left, parsepipe(ptr_to_cmd, shell)));
	}
	return (left);
}

t_node	*parseredirs(t_node *node, char **ptr_to_cmd, t_shell *shell)
{
	int		token;
	int		file_token;
	char 	*ptr_to_token;
	char 	*end_of_token;

	while (peek(ptr_to_cmd, "<>"))
	{
		token = get_token(ptr_to_cmd, 0, 0, shell);
		file_token = get_token(ptr_to_cmd, &ptr_to_token, &end_of_token, shell);
		if (file_token != 'a' && file_token != '$')
		{
			shell->parsing_error = TOKEN_ERROR;
			print_error(1, "Parse error near redirection");
			return (node);
		}
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

t_node	*parseexec(char **ptr_to_cmd, t_shell *shell)
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
		token = get_token(ptr_to_cmd, &ptr_to_token, &end_of_token, shell);
		if (token == 0)
			break ;
		if (token == 'e')
		{
			shell->parsing_error = TOKEN_ERROR;
			print_error(1, "Parse error near quotes");
			return (ret);
		}
		if (token == '$')
			exec_node->av[ac] = ptr_to_token;
		else
			exec_node->av[ac] = ft_substr(ptr_to_token, 0, end_of_token - ptr_to_token);
		ac++;
		if (ac >= MAXARGS)
		{
			shell->parsing_error = TOKEN_ERROR;
			print_error(1, "Max arguments exceeded");
			return (ret);
		}
		ret = parseredirs(ret, ptr_to_cmd, shell);
	}
	exec_node->av[ac] = 0;
	return (ret);
}