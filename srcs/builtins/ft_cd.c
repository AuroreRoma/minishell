/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:50:11 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/11 01:36:28 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_cd(t_cmd *cmd, t_env *env)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd_args[1][0] != '~')
	{
		cd = getcwd(NULL, 0);
		if (!cd)
			exit(1);
		pwd = ft_strjoin(cd, "/");
		free(cd);
		cd = ft_strjoin(pwd, cmd->cmd_args[1]);
		free(pwd);
		return (cd);
	}
	while (env && ft_strcmp(env->env_key, "HOME"))
		env = env->next;
	if (env)
	{
		pwd = ft_substr(cmd->cmd_args[1], 1, ft_strlen(cmd->cmd_args[1]) - 1);
		cd = ft_strjoin(env->env_value, pwd);
		free(pwd);
	}
	return (cd);
}

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*cd;

	cd = NULL;
	if (!cmd->cmd_args[1])
		cmd->cmd_args[1] = ft_strdup("~");
	if (cmd->cmd_args[1][0] == '/' || cmd->cmd_args[1][0] == '.')
		cd = ft_strdup(cmd->cmd_args[1]);
	else
		cd = get_cd(cmd, shell->env);
	if (!cd)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	return (0);
}
