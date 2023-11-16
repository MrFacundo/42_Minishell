/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:30:30 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/15 19:24:43 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_exit_status(char **ptr, char **ptr_to_token, char **end_of_token, int *ret)
{
    *ptr_to_token = ft_itoa(g_shell.exit_code);
    *end_of_token = *ptr_to_token + ft_strlen(*ptr_to_token);
    *ptr = *end_of_token;
    *ret = 'a';
}

void    expand_variable(char **ptr, char **ptr_to_token, char **end_of_token, int *ret)
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
    *ret = 'a';
}


int process_symbol(char **ptr, int ret)
{
    char	*p;
	
	p = *ptr;
	p++;
	if (*p == '>')
	{
		p++;
		ret = '+';
	}
    *ptr = p;
    return (ret);
}

int process_dollar(char **ptr, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    int		ret;
	
	p = *ptr;
	ret = 0;
    p++;
    if (*p == '?')
        expand_exit_status(ptr, ptr_to_token, end_of_token, &ret);
    else
        expand_variable(ptr, ptr_to_token, end_of_token, &ret);
    *ptr = p + ft_strcspn(p, " \t\r\n\v");
    return (ret);
}


int process_default(char **ptr, char **end_of_token, int ret)
{
    char	*p;
	
	p = *ptr;
	ret = 'a';
    p += ft_strcspn(p, " \t\r\n\v<|>&;()");
    if (end_of_token)
        *end_of_token = p;
    p += ft_strspn(p, " \t\r\n\v");
    *ptr = p;
    return (ret);
}

int get_token(char **ptr_to_cmd, char **ptr_to_token, char **end_of_token)
{
    char	*p;
    int		ret;
	
	ret = 0;
	p = *ptr_to_cmd;
	p += ft_strspn(p, " \t\r\n\v");
    if (ptr_to_token)
        *ptr_to_token = p;
    ret = *p;
	if (*p == 0)
		*end_of_token = p;
	else if (*p == '|' || *p == '<' || *p == '>')
		ret = process_symbol(&p, ret);
	else if (*p == '$')
		ret = process_dollar(&p, ptr_to_token, end_of_token);
	else
		ret = process_default(&p, end_of_token, ret);
    *ptr_to_cmd = p;
	// print_token(ret);
    return (ret);
}
