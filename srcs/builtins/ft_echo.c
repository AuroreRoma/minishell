/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:19:02 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 17:31:06 by pblagoje         ###   ########.fr       */
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

	i = 1;
	cmd = shell->first_cmd;
	if (!cmd->cmd_args[1])
	{
		printf("\n");
		return (0);
	}
	while (cmd->cmd_args[i] && cmd->cmd_args[i][0] == '-' && \
			check_n(cmd->cmd_args[i]))
		i++;
	while (cmd->cmd_args[i])
	{
		printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!check_n(cmd->cmd_args[1]))
		printf("\n");
	shell->return_status = 0;
	return (0);
}
