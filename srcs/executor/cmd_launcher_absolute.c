/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher_absolute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/07 18:16:50 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cmd_launcher_absolute(t_shell *shell, t_cmd *cmd)
{
	char	**env;

	env = env_to_str(shell);
	execve(cmd->cmd_name, cmd->cmd_args, env);
	printf("command not found\n");
	free(env);
	exit(0);
}
