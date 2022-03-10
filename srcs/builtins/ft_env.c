/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:52:49 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 18:01:33 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_env_error(t_shell *shell, char *str)
{
	shell->return_status = 127;
	printf("env: %s: No such file or directory\n", str);
}

int	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	if (!env)
		return (1);
	if (shell->first_cmd->cmd_args[1])
	{
		ft_env_error(shell, shell->first_cmd->cmd_args[1]);
		return (shell->return_status);
	}
	while (env)
	{
		printf("%s\n", env->env_full);
		env = env->next;
	}
	return (0);
}
