/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:46:59 by facu              #+#    #+#             */
/*   Updated: 2023/12/03 01:47:38 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	extract_exit_status(char **ptr, char **ret)
{
	char	*expansion;

	expansion = ft_itoa(g_exit_status);
	copy_expansion(ret, expansion);
	(*ptr)++;
}

void	extract_alpha_variable(char **ptr, char **ret, t_shell *shell)
{
	char	*expansion;

	expansion = NULL;
	expand_variable(*ptr, &expansion, shell);
	copy_expansion(ret, expansion);
	(*ptr) += ft_strcspn(*ptr, "\" \t\r\n\v");
}