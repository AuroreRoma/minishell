#include "shell.h"
#include "error.h"

/*
 *	TODO: | " ' < << > >> $ $?
 */

/*
 *	calloc n size
 *	realloc if size is reached
 */

/*
 *	1. op symbol, can add to current op
 *	2. op symbol, can't add, error
 *	3. quote symbol
 *	4. $ symbol
 *	5. op symbol, new symbol
 *	6. skip space
 *	7. add word
 *	8. comment
 *	9. new word
 */

void	*tokenizer(t_lexer *lexer, char *str)
{
	lexer->error = no_error;
	lexer->index = 0;
	lexer->buf_size = TOK_BUFFER_SIZE;
	lexer->tokens = (t_token *)calloc(TOK_BUFFER_SIZE, sizeof(t_token));
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

char	*read_line(void)
{
	static char	*line_read = NULL;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("$> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	main(int ac, char **av, char **env)
{
	bool	break_flag;
	char	*line;
	t_lexer	lexer;
	t_shell	shell;

	break_flag = true;
	(void)ac;
	(void)av;
	(void)env;
	(void)shell;
	while (break_flag)
	{
		line = read_line();
		if (strstr(line, "exit"))
			break ;
		tokenizer(&lexer, line);
		error_lexer(&lexer);
		if (!lexer.error && lexer.index)
			parser(&lexer, &shell);
		destroy_tokens(&lexer, lexer.tokens);
	}
	rl_clear_history();
}
