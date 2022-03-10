/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:28:18 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/09 19:34:04 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	run_builtin(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->first_cmd;
	if (cmd->builtin == builtin_echo)
		return (ft_echo(shell));
	else if (cmd->builtin == builtin_pwd)
		return (ft_pwd(shell));
	return (0);
}
