/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:01 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/05 16:33:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	append_cmd_args(char *str, t_cmd *cmd)
{
	int		i;
	int		old_buffer;
	char	*new;

	i = 0;
	if (!cmd->cmd_args)
		cmd->cmd_args = (char **)ft_calloc(cmd->buffer_size, sizeof(char *));
	if (!cmd->cmd_args)
		return ((printf("Error malloc\n"), 1));
	while (cmd->cmd_args[i])
		i++;
	if (i >= cmd->buffer_size)
	{
		old_buffer = cmd->buffer_size;
		cmd->buffer_size += ARG_BUFFER_SIZE;
		cmd->cmd_args = (char **)ft_calloc(cmd->buffer_size, sizeof(char *));
		if (!cmd->cmd_args)
			return ((printf("Error malloc\n"), 1));
		ft_memset(cmd->cmd_args + old_buffer, 0, ARG_BUFFER_SIZE);
	}
	new = strdup(str);
	if (!new)
		return ((printf("Error malloc\n"), 1));
	cmd->cmd_args[i] = new;
	return (0);
}
