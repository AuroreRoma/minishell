/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:31:22 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/16 18:42:45 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	signal_handler_heredoc(int num)
{
	if (num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit (130);
	}
}

void	signal_handler_exec(int num)
{
	if (num == SIGINT)
		ft_putchar_fd('\n', 1);
	if (num == SIGQUIT)
		ft_putendl_fd(CORE_DUMP, 2);
}

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
