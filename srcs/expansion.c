/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:47:26 by facu              #+#    #+#             */
/*   Updated: 2023/11/18 20:47:41 by facu             ###   ########.fr       */
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
