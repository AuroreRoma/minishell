/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher_absolute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 17:51:16 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cmd_launcher_absolute(t_shell *shell, t_cmd *cmd)
{
	execve(cmd->cmd_name, cmd->cmd_args, shell->env_str);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}
