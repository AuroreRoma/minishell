/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:52:49 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 19:16:10 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = shell->env;
	if (!tmp)
		return (1);
	if (cmd->cmd_args[1])
	{
		print_error_message_exec(cmd->cmd_args[1], NOT_FOUND);
		shell->return_status = 127;
		return (shell->return_status);
	}
	while (tmp)
	{
		if (ft_strchr(tmp->env_full, '='))
			ft_putendl_fd(tmp->env_full, 1);
		tmp = tmp->next;
	}
	return (0);
}
