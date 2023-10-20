/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroiter <ftroiter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:20:06 by ftroiter          #+#    #+#             */
/*   Updated: 2023/10/20 21:48:15 by ftroiter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int getcmd(char *buf)
{
	rl_initialize();
	buf = readline("ms$ ");
	if(buf[0] == 0) // EOF
    	return -1;
	return 0;
}

int	main()
{
  char *buf;

  while(getcmd(buf) >= 0)
  	printf("buf: %s\n", buf);
  return (0);
}