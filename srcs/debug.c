/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:16:48 by ftroiter          #+#    #+#             */
/*   Updated: 2023/11/14 17:18:20 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(int token)
{
	ft_putstr_fd("token: ", 2);
	ft_putchar_fd(token, 2);
	ft_putstr_fd("\n", 2);
}