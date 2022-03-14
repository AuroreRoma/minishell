/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:12:41 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 18:30:35 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
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

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	set_builtins(cmd);
	if (cmd->builtin)
	{
		redirections(cmd);
		run_builtin(shell, cmd);
		dup2(shell->stdio[0], 0);
		dup2(shell->stdio[1], 1);
		return ;
	}
	pid = fork();
	if (!pid)
	{
		redirections(cmd);
		cmd_launcher(shell, cmd);
		exit(1);
	}
	else
		waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		shell->return_status = WEXITSTATUS(wstatus);
	if (WIFSTOPPED(wstatus))
		shell->return_status = WSTOPSIG(wstatus);
}

void	executor(t_shell *shell)
{
	shell->env_str = env_to_str(shell);
	if (shell->nbr_cmd == 1)
		execute_cmd(shell, shell->first_cmd);
	else
		pipeline(shell);
}
