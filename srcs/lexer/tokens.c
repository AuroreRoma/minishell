#include "shell.h"

void	create_token(char *str, int len, t_type type, t_lexer *lexer)
{
	if (lexer->index == lexer->buf_size)
	{
		lexer->tokens = realloc(lexer->tokens, sizeof(t_token) \
			* TOK_BUFFER_SIZE);
		bzero(lexer->tokens + lexer->index, TOK_BUFFER_SIZE);
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

void	destroy_tokens(t_lexer *lexer, t_token *tokens)
{
	int	i;

	i = -1;
	while (++i != lexer->index)
		free(tokens[i].data);
	free(tokens);
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
