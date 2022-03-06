/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 14:09:04 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*join_path(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * len + 2);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '/';
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	**get_path(t_env *envv)
{
	t_env	*tmp;
	char	**str;

	tmp = envv;
	str = NULL;
	while (tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->env_key, "PATH"))
		{
			str = ft_split(tmp->env_value, ':');
			break ;
		}
		tmp = tmp->next;
	}
	return (str);
}

void	ft_free(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	cmd_launcher(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;
	char	**path;
	char	**envv;
	char	*cmd_path;

	i = 0;
	cmd = shell->first_cmd;
	path = get_path(shell->env);
	envv = env_to_str(shell);
	while (path && path[i])
	{
		cmd_path = join_path(path[i], cmd->cmd_name);
		if (execve(cmd_path, cmd->cmd_args, envv) == -1)
		{
			free(cmd_path);
			i++;
		}
	}
	printf("command not found\n");
	ft_free(path);
	free(envv);
	exit(0);
}

void	executor(t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		cmd_launcher(shell);
	else
		wait(NULL);
}
