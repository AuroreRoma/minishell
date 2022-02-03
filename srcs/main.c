#include "shell.h"

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

void	*tokenizer(char *str)
{
	int			buf_size;
	t_tokens	*tokens;

	buf_size = TOK_BUFFER_SIZE
	tokens = (t_token *)calloc(TOK_BUFFER_SIZE, sizeof(t_token));
	if (!tokens)
		return (NULL);
	while (str && *str)
	{
		str += quote(str, &tokens, &buf_size);
		str += dollar(str, &tokens, &buf_size);
		str += operator(str, &tokens, &buf_size);
		str += skip_space(str, &tokens, &buf_size);
		str += append_word(str, &tokens, &buf_size);
		str += comment(str, &tokens, &buf_size);
		str += new_word(str, &tokens, &buf_size);
	}
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

	break_flag = true;
	(void)ac;
	(void)av;
	(void)env;

	while (break_flag)
	{
		line = read_line();
		if (strstr(line, "exit"))
			break ;

		printf("%s\n", line);
	}
	rl_clear_history();
}
