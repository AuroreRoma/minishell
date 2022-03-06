/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:13:36 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 12:51:43 by pblagoje         ###   ########.fr       */
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
	lexer->tokens[lexer->index].data = strndup(str, len);
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
