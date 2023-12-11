/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:47:26 by facu              #+#    #+#             */
/*   Updated: 2023/12/07 15:42:17 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    expand_variable(char *cmd_ptr, char **tkn_ptr, t_shell *shell)
{
    char	*key;
    char	*value;
    
    key = ft_substr(cmd_ptr, 0, ft_strcspn(cmd_ptr, "\" \t\r\n\v"));
    value = ft_get_env(key, shell->env);
    free(key);
    *tkn_ptr = value;
}
