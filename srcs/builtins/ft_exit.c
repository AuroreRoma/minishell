/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:51:32 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 20:52:40 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	(void)shell;
	if (cmd->cmd_args[0])
		printf("exit\n");
	if (cmd->cmd_args[1] && cmd->cmd_args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (cmd->cmd_args[1] && ft_isalldigit(cmd->cmd_args[1]))
		exit(ft_atoi(cmd->cmd_args[1]));
	else if (cmd->cmd_args[1])
	{
		printf("minishell: exit: ");
		printf("%s", cmd->cmd_args[1]);
		printf(": numeric argument required\n");
	}
	else
		exit(0);
	return (0);
}
