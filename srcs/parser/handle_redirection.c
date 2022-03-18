/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:51:52 by marvin            #+#    #+#             */
/*   Updated: 2022/03/18 15:54:31 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "error.h"

static void	__ft_lstadd_back(t_red **alst, t_red *new)
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
	(*index)++;
	join_token(lexer, index);
	(*index)--;
}

static int	__return_status_handler(t_lexer *lexer, int wstatus)
{
	int	ret;

	ret = return_status_handler(wstatus);
	if (ret)
		lexer->error = error_redirection;
	if (ret == 2)
		ret = 0;
	return (ret);
}

void	handle_redirection(\
			t_shell *shell, t_lexer *lexer, t_cmd *current, int *index)
{
	t_red	*new;
	t_type	type;
	int		wstatus;

	wstatus = 0;
	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		lexer->error = error_malloc;
	if (!new)
		return ;
	type = lexer->tokens[*index].type;
	redirection_nbr(lexer, new, index, type);
	if (type == LESS)
		new->type = redir_read;
	if (type == DLESS)
		handle_heredoc(lexer, new, index, &wstatus);
	if (type == GREAT)
		new->type = redir_write;
	if (type == DGREAT)
		new->type = redir_append;
	if (!new->data)
		new->data = ft_strdup(lexer->tokens[(*index) + 1].data);
	__ft_lstadd_back(&current->redirection, new);
	(*index) += 2;
	shell->return_status = __return_status_handler(lexer, wstatus);
}
