/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:07:43 by marvin            #+#    #+#             */
/*   Updated: 2022/03/18 20:39:16 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "error.h"

void	close_all_the_pipes(int n_pipes, int **pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	wait_for_child(t_shell *shell, int *pid)
{
	int		wstatus;
	int		i;
	t_cmd	*current;

	(void)pid;
	wstatus = 0;
	i = 0;
	current = shell->first_cmd;
	while (current)
	{
		waitpid(pid[i], &wstatus, 0);
		if (i == shell->nbr_cmd - 1)
			shell->wstatus = wstatus;
		i++;
		current = current->next;
	}
}

static void	exec_pipeline(t_shell *shell, int **pipe_array, int *pid)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shell->first_cmd;
	while (current && ++i)
	{
		pid[i - 1] = fork();
		if (!pid[i - 1])
		{
			if (current != shell->first_cmd)
				dup2(current->redirect[0], STDIN_FILENO);
			if (current->next)
				dup2(current->redirect[1], STDOUT_FILENO);
			if (redirections(current))
				destroy_child_pipeline(shell, pipe_array, 1, pid);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			close_all_the_pipes(shell->nbr_cmd - 1, pipe_array);
			cmd_launcher(shell, current);
			destroy_child_pipeline(shell, pipe_array, 0, pid);
		}
		current = current->next;
	}
}

static int	**init_pipe(t_shell *shell)
{
	int		i;
	int		**pipe_array;
	t_cmd	*current;

	i = 1;
	current = shell->first_cmd;
	pipe_array = ft_calloc(shell->nbr_cmd, sizeof(int *));
	if (!pipe_array)
		return (NULL);
	while (i < shell->nbr_cmd)
	{
		pipe_array[i - 1] = ft_calloc(2, sizeof(int));
		if (!pipe_array[i - 1])
			return (NULL);
		pipe(pipe_array[i - 1]);
		current->next->redirect[0] = pipe_array[i - 1][0];
		current->redirect[1] = pipe_array[i - 1][1];
		i++;
		current = current->next;
	}
	return (pipe_array);
}

void	pipeline(t_shell *shell)
{
	int	i;
	int	*pid;
	int	**pipe_array;

	set_builtins(shell->first_cmd);
	pipe_array = init_pipe(shell);
	if (!pipe_array)
	{
		print_error_message_exec("malloc", strerror(errno));
		return ;
	}
	pid = calloc(shell->nbr_cmd, sizeof(int));
	exec_pipeline(shell, pipe_array, pid);
	close_all_the_pipes(shell->nbr_cmd - 1, pipe_array);
	wait_for_child(shell, pid);
	free(pid);
	i = 0;
	while (++i < shell->nbr_cmd)
		free(pipe_array[i - 1]);
	free(pipe_array);
}
