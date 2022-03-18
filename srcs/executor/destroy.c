/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:40:03 by aroma             #+#    #+#             */
/*   Updated: 2022/03/18 17:44:19 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	destroy_child_pipeline(t_shell *shell, \
	int **pipe_array, int exit_status, int fl)
{
	int	i;

	if (fl)
		close_all_the_pipes(shell->nbr_cmd - 1, pipe_array);
	i = 0;
	while (++i < shell->nbr_cmd)
		free(pipe_array[i - 1]);
	free(pipe_array);
	destroy_cmd(shell->first_cmd);
	destroy_env_str(shell->env_str);
	clean(shell);
	exit(exit_status);
}

void	destroy_child_exec(t_shell *shell, int exit_status)
{
	destroy_cmd(shell->first_cmd);
	destroy_env_str(shell->env_str);
	clean(shell);
	exit(exit_status);
}
