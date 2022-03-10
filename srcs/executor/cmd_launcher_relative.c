/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher_relative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/10 14:53:53 by marvin           ###   ########.fr       */
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

char	**get_path(t_env *env)
{
	t_env	*tmp;
	char	**str;

	tmp = env;
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

void	cmd_launcher_relative(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	**path;
	char	**env;
	char	*cmd_path;

	i = 0;
	path = get_path(shell->env);
	env = env_to_str(shell);
	while (path && path[i])
	{
		cmd_path = join_path(path[i], cmd->cmd_name);
		if (execve(cmd_path, cmd->cmd_args, env) == -1)
		{
			free(cmd_path);
			i++;
		}
	}
	printf("command not found\n");
	ft_free(path);
	free(env);
	exit(1);
}
