/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/09 19:51:35 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static void	cmd_launcher(t_shell *shell, t_cmd *cmd)
{
	char	*is_absolute;

	if (cmd->cmd_name)
		is_absolute = ft_strchr(cmd->cmd_name, '/');
	else
		return ;
	if (is_absolute)
		cmd_launcher_absolute(shell, cmd);
	else
		cmd_launcher_relative(shell, cmd);
}
/*
static void	launch_builtins(t_shell *shell, t_cmd *current, int *prev_p, \
			int *next_p)
{
	if (current != shell->first_cmd)
	{
		dup2(prev_p[0], 0);
		close(prev_p[0]);
	}
	if (current->next)
	{
		dup2(next_p[1], 1);
		close(next_p[1]);
	}
	redirections(current);
//	builtin();
}
*/
static void	child(t_shell *shell, t_cmd *current, int *prev_p, int *next_p)
{
	if (current != shell->first_cmd)
	{
		dup2(prev_p[0], 0);
		close(prev_p[0]);
	}
	if (current->next)
	{
		dup2(next_p[1], 1);
		close(next_p[1]);
	}
	redirections(current);
//	(void)prev_p;
//	(void)next_p;
	cmd_launcher(shell, current);
	exit(0);
}

static void	parent(t_shell *shell, t_cmd *current, int *prev_p, int *next_p)
{
	int	wstatus;

//	(void)current;
//	(void)prev_p;
//	(void)next_p;
	wait(&wstatus);
	if (current != shell->first_cmd)
		close(prev_p[0]);
	if (current->next)
		close(next_p[1]);
	dup2(shell->stdio[0], 0);
	dup2(shell->stdio[1], 1);
	if (WIFEXITED(wstatus))
		shell->return_status = WEXITSTATUS(wstatus);
	if (WIFSTOPPED(wstatus))
		shell->return_status = WSTOPSIG(wstatus);
}

void	executor(t_shell *shell)
{
	int		pid;
	int		prev_p[2];
	int		next_p[2];
	t_cmd	*current;

	current = shell->first_cmd;
	set_builtins(current); // AJOUT PBLAGOJE
	run_builtin(shell); // AJOUT PBLAGOJE
	while (current)
	{
		if (current != shell->first_cmd)
			ft_memcpy(prev_p, next_p, 2 * sizeof(int));
		if (current->next)
			pipe(next_p);
//		if (is_builtins())
//			launch_builtins(shell, cmd, prev_p, next_p);

//	if (current != shell->first_cmd)
//	{
//		dup2(prev_p[0], 0);
//		close(prev_p[0]);
//	}
//	if (current->next)
//	{
//		dup2(next_p[1], 1);
//		close(next_p[1]);
//	}
	redirections(current);
		pid = fork();
		if (!pid)
			child(shell, current, prev_p, next_p);
		parent(shell, current, prev_p, next_p);
		current = current->next;
	}
	printf("%i\n", shell->return_status);
}
