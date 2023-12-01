/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:47:26 by facu              #+#    #+#             */
/*   Updated: 2023/12/01 16:04:29 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void    expand_variable(char *ptr, char **ptr_to_token, t_shell *shell)
{
    char	*key;
    char	*value;
    
    ptr++;
    key = ft_substr(ptr, 0, ft_strcspn(ptr, " \t\r\n\v"));
    value = ft_get_env(key, shell->env);
    free(key);
    *ptr_to_token = value;
}
