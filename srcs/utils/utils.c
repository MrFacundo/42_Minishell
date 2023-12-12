/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facu <facu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:00 by ftroiter          #+#    #+#             */
/*   Updated: 2023/12/12 00:31:41 by facu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Advances the trailing whitespace and returns 1
	if the current char is in the tokens array */
int	peek(char **pointer_to_cmd, char *tokens)
{
	*pointer_to_cmd += ft_strspn(*pointer_to_cmd, WHITESPACE);
	return (**pointer_to_cmd && ft_strchr(tokens, **pointer_to_cmd));
}

int	close_pipe(int *p)
{
	int	ret;

	ret = close(p[0]);
	if (ret < 0)
		print_error(1, strerror(errno));
	ret = close(p[1]);
	if (ret < 0)
		print_error(1, strerror(errno));
	return (ret);
}

void	print_error(int n, ...)
{
	va_list	args;

	va_start(args, n);
	ft_putstr_fd("minishell", STDERR_FILENO);
	while (n--)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(va_arg(args, char *), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	va_end(args);
}

void	free_strings(char *str, ...)
{
	va_list	args;

	va_start(args, str);
	while (str != 0)
	{
		free(str);
		str = va_arg(args, char *);
	}
	va_end(args);
}
