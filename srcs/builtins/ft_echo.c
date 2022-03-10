/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:02 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/09 19:40:34 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_n(char *flag)
{
	int	i;

	i = 0;
	if (!ft_strcmp(flag, "-n"))
		return (1);
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

int	ft_echo(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->first_cmd;
	if (!cmd->cmd_args[1])
	{
		printf("\n");
		return (0);
	}
	if (cmd->cmd_args[1][0] == '-' && check_n(cmd->cmd_args[1]))
		i = 1;
	while (cmd->cmd_args[++i])
	{
		printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1] != NULL)
			printf(" ");
	}
	if (!check_n(cmd->cmd_args[1]))
		printf("\n");
	shell->return_status = 0;
	return (0);
}
