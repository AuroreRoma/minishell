/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:51:52 by marvin            #+#    #+#             */
/*   Updated: 2022/03/03 17:52:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

/*
	new = create_redirection
	if token = nbr
		if token + 1 = less | dless
			new.fd_out = token.data
		if token + 1 = great | dgreat
			new.fd_in = token.data
		index++
	else
		new.fd_out = 1;
		new.fd_in = 0;
	if token = less
		new.type = redir_read
	if token = dless
		new.type = redir_heredoc
		do_heredoc
	if token = great
		new.type = redir_write
	if token = dgreat
		new.type = redir_append
	if token = sth_else
		error
	new.data = ft_strdup(tokens.data)
	append_to_lst(new)
*/

void	do_heredoc()
{
	printf("Am doing my part ! :D\n");
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

static void	red_nbr(t_lexer *lexer, t_red *new, int *index, int type)
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
	red_nbr(lexer, new, index, type);
	if (type == LESS)
		new->type = redir_read;
	else if (type == DLESS)
	{
		new->type = redir_heredoc;
		do_heredoc();
	}
	else if (type == GREAT)
		new->type = redir_write;
	else if (type == DGREAT)
		new->type = redir_append;
	(*index)++;
	new->data = ft_strdup(lexer->tokens[*index].data);
	__ft_lstadd_back(&current->redirection, new);
	(*index)++;
}
