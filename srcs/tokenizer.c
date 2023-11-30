/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/30 17:48:34 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int process_symbol(char **ptr, int token)
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


int calculate_token_length(char *ptr)
{
    char	*p;
    int		len;
    char	quote;

    p = ptr;
    len = 0;
    quote = 0;
    while (*p)
    {
        if (quote)
        {
            if (*p == quote)
                quote = 0;
        }
        else if (*p == '\'' || *p == '\"')
            quote = *p;
        else if (ft_strchr(" \t\r\n\v<|>&;", *p))
            break ;
        p++;
        len++;
    }
    if (quote)
        return (-1);
    return (len);
}

char *extract_token_without_quotes(char *ptr, int len)
{
    char	*token;
    char	*tmp;
    char	quote;

    quote = 0;
    token = ft_calloc(len + 1, sizeof(char));
    tmp = token;
    while (len--)
    {
        if (quote)
        {
            if (*ptr == quote)
                quote = 0;
            else
                *tmp++ = *ptr;
        }
        else if (*ptr == '\'' || *ptr == '\"')
            quote = *ptr;
        else
            *tmp++ = *ptr;
        ptr++;
    }
    return (token);
}

int process_default(char **ptr, char **ptr_of_token, char **end_of_token)
{
    char	*p;
	int    len;

	p = *ptr;

    len = calculate_token_length(p);
    if (len == -1)
        return ('e');
    *ptr_of_token = extract_token_without_quotes(p, len);
    p += len;
    if (end_of_token)
        *end_of_token = p;
    p += ft_strspn(p, " \t\r\n\v");
    *ptr = p;
    return ('a');
}

int process_dollar(char **ptr, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    int		token;
	
	p = *ptr;
	token = '$';
    p++;
    if (*p == '?')
        *ptr_to_token = ft_itoa(g_shell.exit_status);
    else if (ft_isalpha(*p))
        expand_variable(*ptr, ptr_to_token);
    else
        return process_default(ptr, ptr_to_token, end_of_token);
    *ptr = p + ft_strcspn(p, " \t\r\n\v");
    return (token);
}

int get_token(char **ptr_to_cmd, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    int		token;
	
	token = 0;
	p = *ptr_to_cmd;
	p += ft_strspn(p, " \t\r\n\v");
    if (ptr_to_token)
        *ptr_to_token = p;
    token = *p;
	if (*p == 0)
		*end_of_token = p;
	else if (*p == '|' || *p == '<' || *p == '>')
		token = process_symbol(&p, token);
	else if (*p == '$')
		token = process_dollar(&p, ptr_to_token, end_of_token);
	else
		token = process_default(&p, ptr_to_token, end_of_token);
    *ptr_to_cmd = p;
	// print_token(token);
    return (token);
}