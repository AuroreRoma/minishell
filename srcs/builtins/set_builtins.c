/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:54:32 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/09 18:45:58 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_builtins(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->cmd_name)
		{
			if (!ft_strcmp(cmd->cmd_name, "echo"))
				cmd->builtin = builtin_echo;
			else if (!ft_strcmp(cmd->cmd_name, "cd"))
				cmd->builtin = builtin_cd;
			else if (!ft_strcmp(cmd->cmd_name, "pwd"))
				cmd->builtin = builtin_pwd;
			else if (!ft_strcmp(cmd->cmd_name, "export"))
				cmd->builtin = builtin_export;
			else if (!ft_strcmp(cmd->cmd_name, "unset"))
				cmd->builtin = builtin_unset;
			else if (!ft_strcmp(cmd->cmd_name, "env"))
				cmd->builtin = builtin_env;
			else if (!ft_strcmp(cmd->cmd_name, "exit"))
				cmd->builtin = builtin_exit;
			else
				cmd->builtin = not_builtin;
		}
		cmd = cmd->next;
	}
}
