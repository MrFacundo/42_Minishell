/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:19:55 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/22 21:03:54 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*execnode(void)
{
	t_execnode	*node;

	node = ft_calloc(1, sizeof(t_execnode));
	node->type = EXEC;
	return ((t_node *)node);
}
