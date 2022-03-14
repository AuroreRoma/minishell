/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:21:33 by wind              #+#    #+#             */
/*   Updated: 2022/03/14 19:21:39 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	print_error_message_lexer(char *string, char *token)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(" '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

int		return_status_handler(int wstatus)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		ret = 128;
		ret += WTERMSIG(wstatus);
	}
	return (ret);
}