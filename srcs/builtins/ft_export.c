/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:04:34 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 11:39:46 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	export_add(char *str, t_shell *shell)
{
	char	*key;
	char	*var_full;
	int		i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i] != '+')
		return (0);
	key = ft_substr(str, 0, i);
	var_full = ft_strjoin(key, &str[i + 1]);
	add_env(var_full, shell);
	free(var_full);
	free(key);
	return (1);
}

int	export_update(char *str, t_env *env)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	key = ft_substr(str, 0, i);
	while (env)
	{
		if (!ft_strcmp(env->env_key, key))
		{
			if (env->env_value != NULL)
				free(env->env_value);
			env->env_value = ft_strdup(&str[i + 1]);
			if (env->env_full != NULL)
				free(env->env_full);
			env->env_full = ft_strdup(str);
			free(key);
			return (1);
		}
		env = env->next;
	}
	free(key);
	return (0);
}

void	export_join2(t_env *env, char *key, char *value, char *str)
{
	if (env->env_value != NULL)
	{
		value = ft_strdup(env->env_value);
		free(env->env_value);
		env->env_value = ft_strjoin(value, str);
		free(value);
	}
	else
		env->env_value = ft_strdup(str);
	if (env->env_full != NULL)
		free(env->env_full);
	env->env_full = ft_join_env(key, env->env_value);
	free(key);
}

int	export_join(char *str, t_env *env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	key = ft_substr(str, 0, i);
	while (env)
	{
		if (!ft_strcmp(env->env_key, key))
		{
			export_join2(env, key, value, &str[i + 2]);
			return (1);
		}
		env = env->next;
	}
	free(key);
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
