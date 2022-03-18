/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:51:32 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 14:59:13 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	exit_error(t_shell *shell, char *str, int code)
{
	shell->return_status = code;
	if (code == 1)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	if (code == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean(shell);
		exit(2);
	}
}

static int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	if (cmd->cmd_args[0])
		ft_putendl_fd("exit", 1);
	if (cmd->cmd_args[1] && cmd->cmd_args[2])
	{
		if (!ft_isalldigit(cmd->cmd_args[1]))
			exit_error(shell, cmd->cmd_args[1], 2);
		else
			exit_error(shell, NULL, 1);
		return (1);
	}
	if (cmd->cmd_args[1] && ft_isalldigit(cmd->cmd_args[1]))
	{
		clean(shell);
		exit(ft_atoi(cmd->cmd_args[1]));
	}
	else if (cmd->cmd_args[1])
		exit_error(shell, cmd->cmd_args[1], 2);
	else
	{
		clean(shell);
		exit(0);
	}
	return (0);
}
