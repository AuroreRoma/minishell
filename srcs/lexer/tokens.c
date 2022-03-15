/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:13:36 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/15 18:29:04 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	create_token(char *str, int len, t_type type, t_lexer *lexer)
{
	if (lexer->index == lexer->buf_size)
	{
		lexer->tokens = realloc(lexer->tokens, sizeof(t_token) \
			* TOK_BUFFER_SIZE);
		ft_bzero(lexer->tokens + lexer->index, TOK_BUFFER_SIZE);
		lexer->buf_size += TOK_BUFFER_SIZE;
	}
	lexer->tokens[lexer->index].type = type;
	lexer->tokens[lexer->index].data = ft_strndup(str, len);
	if (!lexer->tokens[lexer->index].data)
	{
		printf("Error malloc\n");
		exit(1);
	}
	lexer->index++;
}

void	dump_tokens(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->index != i)
	{
		printf("[%i][%s]\n", lexer->tokens[i].type, lexer->tokens[i].data);
		i++;
	}
}

void	destroy_tokens(t_lexer *lexer, t_token *tokens)
{
	int	i;

	i = -1;
	while (++i != lexer->index)
		free(tokens[i].data);
	free(tokens);
}

void	*tokenizer(t_lexer *lexer, char *str)
{
	lexer->error = no_error;
	lexer->index = 0;
	lexer->buf_size = TOK_BUFFER_SIZE;
	lexer->tokens = (t_token *)ft_calloc(TOK_BUFFER_SIZE, sizeof(t_token));
	if (!lexer->tokens)
		return (NULL);
	while (str && *str && !lexer->error)
	{
		str += quote(str, lexer);
		str += dollar(str, lexer, VAR);
		str += operator(str, lexer);
		str += skip_space(str, lexer);
		str += word(str, lexer);
		str += comment(str, lexer);
	}
	return (NULL);
}
