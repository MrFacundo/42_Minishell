/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/19 20:31:39 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (peek(&p, "<>|"))
		return ('e');
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
	int		has_quotes;

	has_quotes = 0;
	p = *cmd_ptr;
	len = calculate_token_length(p, shell, &has_quotes);
	if (len == -1)
		return ('e');
	a_token = extract_token(&p, len, shell);
	*tkn_ptr = a_token;
	*cmd_ptr = p;
	if (len == 0 && !has_quotes)
	{
		free(a_token);
		return ('_');
	}
	return ('a');
}

/* 	Sets the token pointer to the token,
	returns the token type,
	Advances the command pointer to the next token */
int	get_token(char **cmd_ptr, char **tkn_ptr, t_shell *shell)
{
	char	*p;
	int		token;

	p = *cmd_ptr;
	p += ft_strspn(p, WHITESPACE);
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
	return (token);
}
