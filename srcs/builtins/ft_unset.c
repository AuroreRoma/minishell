/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:12:25 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/17 22:39:26 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	unset_del_env(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = env->next->next;
	free(tmp->env_full);
	free(tmp->env_key);
	free(tmp->env_value);
	free(tmp);
}

static int	unset_del_first(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strcmp(str, tmp->env_key))
	{
		*env = (*env)->next;
		free(tmp->env_full);
		free(tmp->env_key);
		free(tmp->env_value);
		free(tmp);
		return (1);
	}
	return (0);
}

static void	unset_error(t_shell *shell, char *str, int code)
{
	shell->return_status = code;
	if (code == 1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	if (code == 2)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
}

static int	unset_check_error(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] != '\0')
	{
		unset_error(shell, str, 2);
		shell->return_status = 2;
		return (shell->return_status);
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		unset_error(shell, str, 1);
		shell->return_status = 1;
		return (shell->return_status);
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			unset_error(shell, str, 1);
			shell->return_status = 1;
			return (shell->return_status);
		}
	}
	return (0);
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int		i;
	t_env	*tmp1;
	t_env	*tmp2;

	i = 1;
	while (cmd->cmd_args[i])
	{
		if (unset_check_error(shell, cmd->cmd_args[i]) || !shell->env)
			return (shell->return_status);
		if (unset_del_first(&shell->env, cmd->cmd_args[i]))
			continue ;
		tmp1 = shell->env;
		tmp2 = shell->env->next;
		while (tmp2 && ft_strcmp(tmp2->env_key, cmd->cmd_args[i]))
		{
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp2)
			unset_del_env(tmp1);
		i++;
	}
	return (0);
}
