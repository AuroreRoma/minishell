#include "shell.h"
#include "error.h"

static int	check_redirection(t_lexer *lexer, int i)
{
	if (i + 1 == lexer->index)
	{
		printf("%s: %s `%s'\n", SHELL_NAME, SYNTAX_ERROR, NL);
		lexer->error = error_redirection;
		return (1);
	}
	if (lexer->tokens[i + 1].type == PIPE || \
			is_redirection(lexer->tokens[i + 1].type))
	{
		lexer->error = error_redirection;
		printf("%s: %s `%s'\n", SHELL_NAME, SYNTAX_ERROR, \
				lexer->tokens[i + 1].data);
		return (1);
	}
	return (0);
}

static int	check_pipe(t_lexer *lexer, int i)
{
	if (i + 1 == lexer->index || lexer->tokens[i + 1].type == PIPE || \
			is_redirection(lexer->tokens[i + 1].type))
	{
		lexer->error = error_pipe;
		printf("%s: %s `%s'\n", SHELL_NAME, SYNTAX_ERROR, \
				lexer->tokens[i].data);
		return (1);
	}
	return (0);
}

void	error_lexer(t_lexer	*lexer)
{
	int	i;

	i = 0;
	while (i < lexer->index)
	{
		if (lexer->tokens[i].type == ERROR)
		{
			printf("%s: %s `%s'\n", SHELL_NAME, SYNTAX_ERROR, \
				lexer->tokens[i].data);
			return ;
		}
		if (is_redirection(lexer->tokens[i].type))
		{
			if (check_redirection(lexer, i))
				return ;
		}
		if (lexer->tokens[i].type == PIPE)
			if (check_pipe(lexer, i))
				return ;
		i++;
	}
}
