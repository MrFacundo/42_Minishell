/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/04 19:02:44 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Handles pipes and redirection symbols.
	Sets the pointer to the token,
	returns the token type,
	Advances the command pointer to the next token */
int	process_symbol(char **cmd_ptr, int token)
{
	char	*p;

	p = *cmd_ptr;
	p++;
	if (token == '>' && *p == '>')
	{
		p++;
		token = '+';
	}
	else if (token == '<' && *p == '<')
	{
		p++;
		token = '-';
	}
	*cmd_ptr = p;
	return (token);
}

/* Handles all alphanumeric tokens, including quotes and expansions.
	Sets the pointer to the token, returns the token type,
	Advances the command pointer to the next token */
int	process_default(char **cmd_ptr, char **tkn_ptr, t_shell *shell)
{
	char	*p;
	int		len;
	char	*a_token;

	p = *cmd_ptr;
	len = calculate_token_length(p, shell);
	if (len == -1)
		return ('e');
	a_token = extract_token(&p, len, shell);
	*tkn_ptr = a_token;
	*cmd_ptr = p;
	return ('a');
}

/* 	Sets the token pointer to the token,
	returns the token type,
	Advances the command pointer to the next token */
int	get_token(char **cmd_ptr, char **tkn_ptr, t_shell *shell)
{
	char *p;
	int token;

	p = *cmd_ptr;
	p += ft_strspn(p, " \t\r\n\v");
	if (tkn_ptr)
		*tkn_ptr = p;
	token = *p;
	if (*p == 0)
		;
	else if (*p == '|' || *p == '<' || *p == '>')
		token = process_symbol(&p, token);
	else
		token = process_default(&p, tkn_ptr, shell);
	*cmd_ptr = p;
	//print_token(token);
	return (token);
}