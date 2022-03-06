/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 16:57:59 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	executor(t_shell *shell)
{
	int		pid;
	char	*is_absolute;

	is_absolute = ft_strchr(shell->first_cmd->cmd_name, '/');
	pid = fork();
	if (pid == 0)
	{
		if (is_absolute)
			cmd_launcher_absolute(shell);
		else
			cmd_launcher_relative(shell);
	}
	else
		wait(NULL);
}
