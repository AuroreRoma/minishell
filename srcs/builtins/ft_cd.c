/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:50:11 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/17 22:43:13 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	cd_update_env(t_shell **shell)
{
	t_env	*tmp_pwd;
	t_env	*tmp_oldpwd;

	tmp_pwd = (*shell)->env;
	tmp_oldpwd = (*shell)->env;
	while (tmp_pwd && ft_strcmp(tmp_pwd->env_key, "PWD"))
		tmp_pwd = tmp_pwd->next;
	while (tmp_oldpwd && ft_strcmp(tmp_oldpwd->env_key, "OLDPWD"))
		tmp_oldpwd = tmp_oldpwd->next;
	if (tmp_pwd && tmp_oldpwd)
	{
		free(tmp_oldpwd->env_value);
		tmp_oldpwd->env_value = ft_strdup(tmp_pwd->env_value);
		free(tmp_pwd->env_value);
		tmp_pwd->env_value = getcwd(NULL, 0);
	}
}

char	*get_cd(t_cmd *cmd, t_env *env)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd_args[1][0] != '~')
	{
		cd = getcwd(NULL, 0);
		if (!cd)
			return (NULL);
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

	if (!cmd->cmd_args[1])
		cmd->cmd_args[1] = ft_strdup("~");
	if (cmd->cmd_args[1][0] == '/' || cmd->cmd_args[1][0] == '.')
		cd = ft_strdup(cmd->cmd_args[1]);
	else
		cd = get_cd(cmd, shell->env);
	if (!cd)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (access(cd, F_OK) == 0)
	{
		if (chdir(cd) != 0)
			print_error_message_exec(cmd->cmd_args[1], NOT_DIRECTORY);
		else
			cd_update_env(&shell);
	}
	else
		print_error_message_exec(cmd->cmd_args[1], NOT_FOUND);
	free(cd);
	shell->return_status = 1;
	return (shell->return_status);
}
