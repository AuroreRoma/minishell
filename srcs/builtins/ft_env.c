/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:52:49 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/13 19:31:10 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_env_error(t_shell *shell, char *str)
{
	shell->return_status = 127;
	ft_putstr_fd("minishell: env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = shell->env;
	if (!tmp)
		return (1);
	if (cmd->cmd_args[1])
	{
		ft_env_error(shell, cmd->cmd_args[1]);
		return (shell->return_status);
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->env_full, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
