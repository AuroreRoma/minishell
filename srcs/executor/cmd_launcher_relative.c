/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher_relative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 20:50:20 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

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
	char	**str;

	str = NULL;
	while (env)
	{
		if (!ft_strcmp(env->env_key, "PATH"))
		{
			if (!ft_strchr(env->env_value, ':'))
			{
				str = (char **)ft_calloc(2, sizeof(char *));
				str[0] = ft_strdup(env->env_value);
				str[1] = NULL;
			}
			else
				str = ft_split(env->env_value, ':');
			break ;
		}
		env = env->next;
	}
	return (str);
}

void	ft_free(char **path)
{
	int	i;

	i = 0;
	if (path == NULL)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	cmd_print_error(char **path, char *cmd_name, int e)
{
	(void)path;
	if (e == EACCES)
		print_error_message_exec(cmd_name, strerror(e));
	else if (!path)
		print_error_message_exec(cmd_name, NOT_FOUND);
	else
		print_error_message_exec(cmd_name, NO_COMMAND);
}

void	cmd_launcher_relative(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		e;
	char	**path;
	char	*cmd_path;

	i = 0;
	e = 0;
	path = get_path(shell->env);
	while (path && path[i])
	{
		cmd_path = join_path(path[i], cmd->cmd_name);
		if (execve(cmd_path, cmd->cmd_args, shell->env_str) == -1)
		{
			i++;
			if ((errno == EACCES && !is_directory(cmd_path)))
				e = errno;
			free(cmd_path);
		}
	}
	cmd_print_error(path, cmd->cmd_name, e);
	ft_free(path);
	destroy_child_exec(shell, 126 + (e != EACCES));
}

	// dont care if the file is a directory
	// permision issue 126
	// bash: ./README.md: Permission denied
	// keep first error incase command not found

	// if command not found else 127
	// bash: foo: command not found
