/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:31:22 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 15:23:42 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	signal_handler(int num)
{
	if (num == SIGQUIT && is_reading_line(-1))
	{
		rl_replace_line("  ", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (num == SIGQUIT)
		ft_putendl_fd(CORE_DUMPED, 2);
	if (num == SIGINT && is_reading_line(-1))
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
