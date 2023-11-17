/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/17 01:12:30 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_exit_status(char **ptr, char **ptr_to_token, char **end_of_token)
{
    *ptr_to_token = ft_itoa(g_shell.exit_code);
    *end_of_token = *ptr_to_token + ft_strlen(*ptr_to_token);
    *ptr = *end_of_token;
}

void    expand_variable(char **ptr, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    char	*key;
    char	*value;
    
    p = *ptr;
    p++;
    key = ft_substr(p, 0, ft_strcspn(p, " \t\r\n\v"));
    value = ft_get_env(key, g_shell.env);
    *ptr_to_token = value;
    *end_of_token = value + ft_strlen(value); 
    *ptr = *end_of_token;
}

int process_symbol(char **ptr, int token)
{
    char	*p;
	
	p = *ptr;
	p++;
	if (*p == '>')
	{
		p++;
		token = '+';
	}
    *ptr = p;
    return (token);
}

int process_dollar(char **ptr, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    int		token;
	
	p = *ptr;
	token = 'a';
    p++;
    if (*p == '?')
        expand_exit_status(ptr, ptr_to_token, end_of_token);
    else if (ft_isalpha(*p))
        expand_variable(ptr, ptr_to_token, end_of_token);
    else
        *end_of_token = p + ft_strcspn(p, " \t\r\n\v");
    *ptr = p + ft_strcspn(p, " \t\r\n\v");
    return (token);
}


int process_default(char **ptr, char **end_of_token, int token)
{
    char	*p;
	
	p = *ptr;
	token = 'a';
    p += ft_strcspn(p, " \t\r\n\v<|>&;()");
    if (end_of_token)
        *end_of_token = p;
    p += ft_strspn(p, " \t\r\n\v");
    *ptr = p;
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
		token = process_default(&p, end_of_token, token);
    *ptr_to_cmd = p;
	// print_token(token);
    return (token);
}
