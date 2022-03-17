/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:04:34 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/17 01:21:58 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	export_add(char *str, t_shell *shell)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i] != '+')
		return (0);
	var = ft_strjoin(ft_substr(str, 0, i), "=");
	var = ft_strjoin(var, &str[i + 2]);
	add_env(var, shell);
	free(var);
	return (1);
}

int	export_update(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	while (env)
	{
		if (!ft_strcmp(env->env_key, ft_substr(str, 0, i)))
		{
			if (env->env_value)
				env->env_value = NULL;
			env->env_value = ft_strdup(&str[i + 1]);
			if (env->env_full)
				env->env_full = NULL;
			env->env_full = ft_strdup(str);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	export_join(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i] == '=')
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->env_key, ft_substr(str, 0, i)))
		{
			if (env->env_value)
				env->env_value = ft_strjoin(env->env_value, &str[i + 2]);
			else
				env->env_value = ft_strdup(&str[i + 2]);
			if (env->env_full)
			{
				env->env_full = ft_strjoin(ft_substr(str, 0, i), "=");
				env->env_full = ft_strjoin(env->env_full, &str[i + 2]);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	export_no_args(t_shell *shell)
{
	t_env	*tmp;

	sort_env(shell);
	tmp = shell->env_sorted;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->env_full);
		tmp = tmp->sorted_next;
	}
	return (0);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	shell->return_status = 0;
	if (!cmd->cmd_args[1])
		return (export_no_args(shell));
	while (cmd->cmd_args[++i])
	{
		if (export_check_args(shell, cmd->cmd_args[i]))
			continue ;
		if (ft_strchr(cmd->cmd_args[i], '+') && \
			ft_strchr(cmd->cmd_args[i], '=') && \
			export_join(cmd->cmd_args[i], shell->env))
			continue ;
		if (export_update(cmd->cmd_args[i], shell->env))
			continue ;
		if (!export_add(cmd->cmd_args[i], shell))
			add_env(cmd->cmd_args[i], shell);
	}
	return (shell->return_status);
}
