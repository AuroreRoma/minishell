/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher_absolute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 17:45:19 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	cmd_launcher_absolute(t_shell *shell, t_cmd *cmd)
{
	execve(cmd->cmd_name, cmd->cmd_args, shell->env_str);
	if (errno == EACCES && is_directory(cmd->cmd_name))
		print_error_message_exec(cmd->cmd_name, DIRECTORY);
	else
		print_error_message_exec(cmd->cmd_name, strerror(errno));
	destroy_child_exec(shell, 126 + (errno != EACCES));
}
