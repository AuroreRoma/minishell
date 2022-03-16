/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/16 18:42:41 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"
#include "libft.h"

void	cmd_launcher(t_shell *shell, t_cmd *cmd)
{
	char	*is_absolute;

	if (cmd->builtin)
	{
		run_builtin(shell, cmd);
		return ;
	}
	if (cmd->cmd_name)
		is_absolute = ft_strchr(cmd->cmd_name, '/');
	else
		return ;
	if (is_absolute)
		cmd_launcher_absolute(shell, cmd);
	else
		cmd_launcher_relative(shell, cmd);
}

static void	handle_child(t_shell *shell, t_cmd *cmd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (redirections(cmd))
		exit(1);
	cmd_launcher(shell, cmd);
	exit(1);
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	set_builtins(cmd);
	if (cmd->builtin)
	{
		if (redirections(cmd))
		{
			perror("Placeholder redirection error:");
			shell->return_status = 1;
			return ;
		}
		run_builtin(shell, cmd);
		dup2(shell->stdio[0], 0);
		dup2(shell->stdio[1], 1);
		return ;
	}
	pid = fork();
	if (!pid)
		handle_child(shell, cmd);
	else
		waitpid(pid, &wstatus, 0);
	shell->return_status = wstatus;
}

void	executor(t_shell *shell)
{
	signal(SIGINT, &signal_handler_exec);
	signal(SIGQUIT, &signal_handler_exec);
	shell->env_str = env_to_str(shell);
	if (shell->nbr_cmd == 1)
		execute_cmd(shell, shell->first_cmd);
	else
		pipeline(shell);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	shell->return_status = return_status_handler(shell->return_status);
}
