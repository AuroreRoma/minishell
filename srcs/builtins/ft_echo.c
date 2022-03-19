/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:02 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/19 12:55:59 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_n(char *flag)
{
	int	i;

	i = 0;
	if (!ft_strcmp(flag, "-n"))
		return (1);
	if (!flag[0])
		return (0);
	if (flag[0] == '-')
		i++;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 1;
	if (!cmd->cmd_args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (cmd->cmd_args[i] && cmd->cmd_args[i][0] == '-' && \
			check_n(cmd->cmd_args[i]))
		i++;
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		if (cmd->cmd_args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!check_n(cmd->cmd_args[1]))
		ft_putstr_fd("\n", 1);
	shell->return_status = 0;
	return (0);
}
