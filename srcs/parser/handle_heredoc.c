/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:50:04 by aroma             #+#    #+#             */
/*   Updated: 2022/03/19 14:43:43 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"
#include "libft.h"

static char	*_read_line(char *word, int fd)
{
	static int	line = 0;
	static char	*line_read = NULL;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline(HEREDOC_PROMPT);
	line++;
	if (line_read == NULL)
	{
		print_error_message_heredoc(word, line);
		free(line_read);
		close(fd);
		free_heredoc(NULL, NULL, NULL, 2);
	}
	return (line_read);
}

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
			((ft_strlen(buf)) == ft_strlen(word) - offset))
		return (1);
	return (0);
}

void	get_heredoc(char *word, t_red *new)
{
	int			fd;
	char		*buf;

	fd = open(new->data, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	buf = _read_line(word, fd);
	while (1)
	{
		if (check_heredoc_end(word, buf))
			break ;
		ft_putendl_fd(buf, fd);
		buf = _read_line(word, fd);
	}
	close(fd);
}

void	free_heredoc(t_shell *shell, t_lexer *lexer, t_red *new, int flag)
{
	static t_shell	*sh = NULL;
	static t_lexer	*le = NULL;
	static t_red	*re = NULL;

	if (flag == -1)
	{
		sh = shell;
		le = lexer;
		re = new;
		return ;
	}
	destroy_cmd(sh->first_cmd);
	destroy_tokens(le, le->tokens);
	clean(sh);
	free(re->data);
	free(re);
	exit(flag);
}

void	handle_heredoc(t_shell *shell, t_lexer *lexer, t_red *new, int *index)
{
	int		pid;
	char	*ptr;
	char	*filename;

	filename = generate_herefile_name();
	new->data = filename;
	new->type = redir_heredoc;
	if (ft_strchr(lexer->tokens[*index + 1].data, '\'') || \
		ft_strchr(lexer->tokens[*index + 1].data, '\"'))
		new->flag = 1;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		free_heredoc(shell, lexer, new, -1);
		signal(SIGINT, &signal_handler_heredoc);
		ptr = remove_quote(lexer->tokens[*index + 1].data);
		free(lexer->tokens[*index + 1].data);
		lexer->tokens[*index + 1].data = ptr;
		get_heredoc(lexer->tokens[*index + 1].data, new);
		free_heredoc(shell, lexer, new, 0);
	}
	wait(&shell->wstatus);
	signal(SIGINT, &signal_handler);
}
