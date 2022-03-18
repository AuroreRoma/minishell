/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:43:29 by marvin            #+#    #+#             */
/*   Updated: 2022/03/18 15:42:48 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

static int	check_redirection(t_lexer *lexer, int i)
{
	if (i + 1 == lexer->index)
	{
		print_error_message_lexer(SYNTAX_ERROR, NL);
		lexer->error = error_redirection;
		return (1);
	}
	if (lexer->tokens[i + 1].type == PIPE || \
			is_redirection(lexer->tokens[i + 1].type))
	{
		lexer->error = error_redirection;
		print_error_message_lexer(SYNTAX_ERROR, lexer->tokens[i + 1].data);
		return (1);
	}
	return (0);
}

static int	check_pipe(t_lexer *lexer, int i)
{
	if (i + 1 == lexer->index || lexer->tokens[i + 1].type == PIPE \
		|| (lexer->tokens[0].type == PIPE))
	{
		lexer->error = error_pipe;
		print_error_message_lexer(SYNTAX_ERROR, lexer->tokens[i].data);
		return (1);
	}
	return (0);
}

int	error_lexer(t_lexer	*lexer)
{
	int	i;

	i = 0;
	if (lexer->error == error_malloc)
		ft_putstr_fd("Error malloc : Exit program promptly\n", 2);
	if (lexer->error == error_malloc)
		exit(2);
	while (i < lexer->index)
	{
		if (lexer->tokens[i].type == ERROR)
		{
			print_error_message_lexer(SYNTAX_ERROR, lexer->tokens[i].data);
			return (2);
		}
		if (is_redirection(lexer->tokens[i].type))
		{
			if (check_redirection(lexer, i))
				return (2);
		}
		if (lexer->tokens[i].type == PIPE)
			if (check_pipe(lexer, i))
				return (2);
		i++;
	}
	return (0);
}
