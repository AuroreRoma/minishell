/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:15:04 by pblagoje          #+#    #+#             */
/*   Updated: 2022/02/24 20:22:16 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_pipe(t_cmd **current, int *index)
{
	(*current) = (*current)->next;
	(*index)++;
}

void	handle_word(t_lexer *lexer, t_cmd *current, int *index)
{
	if (!current->cmd_name)
	{
		current->cmd_name = strdup(lexer->tokens[*index].data);
		if (!current->cmd_name)
			printf("Error malloc\n");
	}
	if (append_cmd_args(lexer->tokens[*index].data, current))
		exit(1);
	(*index)++;
}

static int	check_condition(t_type type, char flag)
{
	if (flag == '<')
	{
		if (type == LESS || type == DLESS)
			return (1);
		else
			return (0);
	}
	else if (flag == '>')
	{
		if (type == GREAT || type == DGREAT)
			return (1);
		else
			return (0);
	}
	return (0);
}

static void	handle_redirection_2(t_lexer *lexer, t_cmd *current, int *index)
{
	if (check_condition(lexer->tokens[*index - 1].type, '>'))
		current->filename_out = strdup(lexer->tokens[*index].data);
	else if (check_condition(lexer->tokens[*index - 1].type, '<'))
		current->filename_in = strdup(lexer->tokens[*index].data);
	else
		current->heredoc_end = strdup(lexer->tokens[*index].data);
}

void	handle_redirection(t_lexer *lexer, t_cmd *current, int *index)
{
	if (lexer->tokens[*index].type == NBR && \
			check_condition(lexer->tokens[*index + 1].type, '<'))
		current->fd_out = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR && \
			check_condition(lexer->tokens[*index + 1].type, '>'))
		current->fd_in = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR)
		(*index) += 1;
	else if (check_condition(lexer->tokens[*index].type, '<'))
		current->fd_out = 1;
	else if (check_condition(lexer->tokens[*index].type, '>'))
		current->fd_in = 0;
	else
		printf("Error\n");
	(*index) += 1;
	if (lexer->tokens[*index].type == WORD)
		handle_redirection_2(lexer, current, index);
	else
		printf("\x1B[31mshell: parse error near `%s'\x1B[0m\n", \
				lexer->tokens[*index].data);
	(*index) += 1;
}
