/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/02 18:58:04 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_symbol(char **ptr, int token)
{
	char	*p;

	p = *ptr;
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
	*ptr = p;
	return (token);
}

int	process_default(char **ptr, char **ptr_of_token, t_shell *shell)
{
	char	*p;
	int		len;
	char	*a_token;

	p = *ptr;
	len = calculate_token_length(p, shell);
	if (len == -1)
		return ('e');
	a_token = extract_token(&p, len, shell);
	*ptr_of_token = a_token;
	*ptr = p;
	return ('a');
}

int	get_token(char **ptr_to_cmd, char **ptr_to_token, t_shell *shell)
{
	char *p;
	int token;

	token = 0;
	p = *ptr_to_cmd;
	p += ft_strspn(p, " \t\r\n\v");
	if (ptr_to_token)
		*ptr_to_token = p;
	token = *p;
	if (*p == 0)
		;
	else if (*p == '|' || *p == '<' || *p == '>')
		token = process_symbol(&p, token);
	else
		token = process_default(&p, ptr_to_token, shell);
	*ptr_to_cmd = p;
	// print_token(token);
	return (token);
}