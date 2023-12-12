/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:46:59 by facu              #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variable(char *cmd_ptr, char **tkn_ptr, t_shell *shell)
{
	char	*key;
	char	*value;

	key = ft_substr(cmd_ptr, 0, ft_strcspn(cmd_ptr, "\" \t\r\n\v"));
	value = ft_get_env(key, shell->env);
	free(key);
	*tkn_ptr = value;
}

void	copy_expansion(char **ret, char *expansion)
{
	size_t	len;

	if (expansion)
	{
		len = ft_strlen(expansion);
		ft_strlcpy(*ret, expansion, len + 1);
		*ret += len;
		free(expansion);
	}
}

void	extract_exit_status(char **cmd_ptr, char **ret)
{
	char	*expansion;

	expansion = ft_itoa(g_exit_status);
	copy_expansion(ret, expansion);
	(*cmd_ptr)++;
}

void	extract_alpha_variable(char **cmd_ptr, char **ret, t_shell *shell)
{
	char	*expansion;

	expansion = NULL;
	expand_variable(*cmd_ptr, &expansion, shell);
	copy_expansion(ret, expansion);
	(*cmd_ptr) += ft_strcspn(*cmd_ptr, "\" \t\r\n\v");
}
