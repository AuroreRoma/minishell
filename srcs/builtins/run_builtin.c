/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:28:18 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 18:48:53 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == builtin_echo)
		return (ft_echo(shell));
	else if (cmd->builtin == builtin_pwd)
		return (ft_pwd(shell));
	else if (cmd->builtin == builtin_env)
		return (ft_env(shell));
	else if (cmd->builtin == builtin_exit)
		return (ft_exit(shell));
	return (0);
}
