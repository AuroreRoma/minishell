/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:51:52 by marvin            #+#    #+#             */
/*   Updated: 2022/03/11 15:37:39 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "gnl.h"

int	check_heredoc_end(char *word, char *buf)
{
	int	offset;

	offset = 0;
	if ((*word) == '\'' || (*word) == '\"')
	{
		offset = 1;
		word++;
	}
	if (!ft_strncmp(word, buf, ft_strlen(word) - offset) && \
			((ft_strlen(buf) - 1) == ft_strlen(word) - offset))
		return (1);
	return (0);
}

char	*generate_herefile_name(void)
{
	char		*str;
	char		*ret;
	static int	n_file = 0;

	n_file++;
	if ((n_file) == 32)
		n_file = 0;
	ret = ft_itoa(n_file);
	str = ft_strjoin(".herefile_", ret);
	free(ret);
	ret = ft_strjoin(str, ".tmp");
	free(str);
	return (ret);

}

void	do_heredoc(char *word, t_red *new)
{
	int			fd;
	int			gnl;
	char		*buf;
	char		*filename;

	filename = generate_herefile_name();
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	write(1, "> ", ft_strlen("> "));
	gnl = get_next_line(0, &buf);
	while (gnl == 1)
	{
		if (check_heredoc_end(word, buf))
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
		write(1, "> ", ft_strlen("> "));
		gnl = get_next_line(0, &buf);
	}
	if (!gnl)
		printf("error\n");
	free(buf);
	close(fd);
	new->data = filename;
}

void	__ft_lstadd_back(t_red **alst, t_red *new)
{
	t_red	*current;

	if (*alst == NULL)
		*alst = new;
	else
	{
		current = *alst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

static void	redirection_nbr(t_lexer *lexer, t_red *new, int *index, int type)
{
	if (lexer->tokens[*index].type == NBR)
	{
		type = lexer->tokens[*index + 1].type;
		if (type == LESS || type == DLESS)
			new->fd_out = ft_atoi(lexer->tokens[*index].data);
		if (type == GREAT || type == DGREAT)
			new->fd_in = ft_atoi(lexer->tokens[*index].data);
		(*index)++;
	}
	else
	{
		new->fd_out = 1;
		new->fd_in = 0;
	}
}

void	handle_redirection(t_lexer *lexer, t_cmd *current, int *index)
{
	t_red	*new;
	t_type	type;

	new = ft_calloc(1, sizeof(t_red));
	type = lexer->tokens[*index].type;
	redirection_nbr(lexer, new, index, type);
	if (type == LESS)
		new->type = redir_read;
	if (type == DLESS)
	{
		new->type = redir_heredoc;
		do_heredoc(lexer->tokens[*index + 1].data, new);
		if (lexer->tokens[*index + 1].type == QUOTE || \
				lexer->tokens[*index + 1].type == DQUOTE)
			new->flag = 1;
	}
	if (type == GREAT)
		new->type = redir_write;
	if (type == DGREAT)
		new->type = redir_append;
	(*index)++;
	if (!new->data)
		new->data = ft_strdup(lexer->tokens[*index].data);
	__ft_lstadd_back(&current->redirection, new);
	(*index)++;
}
