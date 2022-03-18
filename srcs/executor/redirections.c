/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:12:10 by marvin            #+#    #+#             */
/*   Updated: 2022/03/18 16:06:13 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

int	open_fd(t_red *red)
{
	int	fd;

	if (red->type == redir_append)
		fd = open(red->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (red->type == redir_write)
		fd = open(red->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (red->type == redir_read || red->type == redir_heredoc)
		fd = open(red->data, O_RDONLY);
	return (fd);
}

int	redirections(t_cmd *cmd)
{
	int		fd;
	t_red	*current;

	current = cmd->redirection;
	while (current)
	{
		fd = open_fd(current);
		if (fd == -1)
		{
			print_error_message_exec(current->data, strerror(errno));
			return (1);
		}
		if (current->type == redir_append || current->type == redir_write)
			dup2(fd, current->fd_out);
		if (current->type == redir_read || current->type == redir_heredoc)
			dup2(fd, current->fd_in);
		close(fd);
		current = current->next;
	}
	return (0);
}
