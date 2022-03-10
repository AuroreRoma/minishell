/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:28:18 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 17:16:25 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == builtin_echo)
		return (ft_echo(shell));
	else if (cmd->builtin == builtin_pwd)
		return (ft_pwd(shell));
	return (0);
}
