/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_redirec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:19:50 by wind              #+#    #+#             */
/*   Updated: 2022/03/18 16:03:21 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "gnl.h"

static void	clean_func(char *str, char *line, int fd1, int fd2)
{
	unlink(str);
	free(str);
	free(line);
	close(fd1);
	close(fd2);
}

void	var_expansion_heredoc(t_shell *shell, t_red *current)
{
	int		gnl;
	int		old_fd;
	int		new_fd;
	char	*line;
	char	*filename;

	old_fd = open(current->data, O_RDONLY);
	filename = generate_herefile_name();
	new_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0777);
	gnl = get_next_line(old_fd, &line);
	while (gnl == 1)
	{
		search_and_replace_var(shell, &line);
		write(new_fd, line, ft_strlen(line));
		free(line);
		gnl = get_next_line(old_fd, &line);
	}
	clean_func(current->data, line, old_fd, new_fd);
	current->data = filename;
}

void	var_expansion_redirection(t_shell *shell, t_red *current)
{
	while (current)
	{
		var_replace_line(shell, &current->data);
		if (current->type == redir_heredoc && !current->flag)
			var_expansion_heredoc(shell, current);
		current = current->next;
	}
}
