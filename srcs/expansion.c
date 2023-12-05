/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:47:26 by facu              #+#    #+#             */
/*   Updated: 2023/12/04 23:52:18 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    expand_variable(char *ptr, char **tkn_ptr, t_shell *shell)
{
    char	*key;
    char	*value;
    
    key = ft_substr(ptr, 0, ft_strcspn(ptr, "\" \t\r\n\v"));
    value = ft_get_env(key, shell->env);
    free(key);
    *tkn_ptr = value;
}
