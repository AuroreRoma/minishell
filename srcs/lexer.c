#include "shell.h"

/*
 *int	length_array(t_token *tokens)
 *{
 *	int	length;
 *
 *	length = 0;
 *	while (tokens[length].e_type)
 *		length++;
 *	return (length);
 *}
 */

static void	quote_helper(char **start, char **str, char *quote, int *len)
{
	*start = *str;
	*quote = **str;
	(*str)++;
	*len = 0;
}

/*	while (str[len] && str[len] != quote)
		if (quote == '\"' && str[len] == '$')
		{
			if (len)
				create_token(str, len, QUOTE, lexer);
			str += len + dollar(str + len, lexer, VAR_QUOTE);
//			len_var = size_var(str + len, quote);
//			create_token(str, len, VAR, lexer);
//			str += len + len_var;
			len = 0;
		}
		else
*/

int	quote(char *str, t_lexer *lexer)
{
	int		len;
	char	quote;
	char	*start;

	if (!(*str == '\'' || *str == '\"'))
		return (0);
	quote_helper(&start, &str, &quote, &len);
	while (str[len] && str[len] != quote)
		len++;
	if (len && str[len] == quote)
	{
		if (quote == '\'')
			create_token(str, len, QUOTE, lexer);
		else
			create_token(str, len, DQUOTE, lexer);
	}
	else if (str[len] != quote)
	{
		lexer->error = error_quote;
		return (0);
	}
	return ((str + len + 1) - start);
}

int	dollar(char *str, t_lexer *lexer, t_type type)
{
	int		len_var;
	char	*start;

	start = str;
	if ((*str) != '$')
		return (0);
	str++;
	if (*str == '{' && str++)
	{
		len_var = size_var(str, '}');
		create_token(str, len_var, type, lexer);
		return ((str + len_var + 1) - start);
	}
	len_var = size_var(str, 0);
	create_token(str, len_var, type, lexer);
	return ((str + len_var) - start);
}
/*
   int	dollar(char *str, t_token **tokens, int *buf_size)
   {
   int	skip;
   int	length;

   if (*str != '$')
   return (0);
   length = length_array(*tokens);
   if (length == *buf_size)	// put in seperate function
   {
   realloc(*tokens, sizeof(t_token) * TOK_BUFFER_SIZE);
   bzero(*tokens + length, TOK_BUFFER_SIZE);
   buf_size += TOK_BUFFER_SIZE;
   }
   }
   */

int	operator(char *str, t_lexer *lexer)
{
	int	ret;

	ret = 1;
	if (!is_operator(*str))
		return (0);
	if (*str == '|' && *(str + 1) != '|')
		create_token(str, 1, PIPE, lexer);
	else if (*str == '<' && *(str + 1) == '<' && ret++)
		create_token(str, 2, DLESS, lexer);
	else if (*str == '<' && *(str + 1) != '<')
		create_token(str, 1, LESS, lexer);
	else if (*str == '>' && *(str + 1) == '>' && ret++)
		create_token(str, 2, DGREAT, lexer);
	else if (*str == '>' && *(str + 1) != '>')
		create_token(str, 1, GREAT, lexer);
	else if (is_operator(*(str + 1)))
		lexer->error = error_operator;
	return (ret);
}

int	word(char *str, t_lexer *lexer)
{
	int		len;

	len = 0;
	if (str[len] == '#')
		return (0);
	while (str[len] && !is_operator(str[len]) && str[len] != '\'' && \
			str[len] != '\"' && str[len] != ' ' && str[len] != '$')
		len++;
	if (len && !is_number(str, len))
		create_token(str, len, WORD, lexer);
	else if (len)
		create_token(str, len, NBR, lexer);
	return (len);
}

/*
int	main(void)
{
	t_token *tokens = calloc(12, sizeof(t_token));
	t_lexer lexer;

	lexer = (t_lexer){12, 0, tokens};
	printf("Return value : %i\n", \
			quote("\"Hello world $RANDOM\"", &lexer));
	printf("Correct value : %i\n", strlen("\"Hello world $RANDOM\""));
	dump_tokens(&lexer);
	free(tokens);
	tokens = calloc(12, sizeof(t_token));
	lexer = (t_lexer){12, 0, tokens};
	printf("Return value : %i\n", \
		quote("\'Hello world $MOAR_RANDOM\'", &lexer));
	printf("Correct value : %i\n", strlen("\'Hello world $MOAR_RANDOM\'"));
	dump_tokens(&lexer);
	free(tokens);
	tokens = calloc(12, sizeof(t_token));
	lexer = (t_lexer){12, 0, tokens};
	printf("%i\n",dollar("$MORE_STUFF", &lexer));
	printf("%i\n",dollar("${MORE_STUFF}", &lexer));
	printf("%i\n",dollar("$MORE_STUFF\"\"\"", &lexer));
	printf("%i\n", operator("|", &lexer));
	printf("%i\n", operator("||", &lexer));
	printf("%i\n", operator("<<", &lexer));
	printf("%i\n", word("abc def", &lexer));
 	printf("%i\n", word("abcdef", &lexer));
 	printf("%i\n", word("abc#|| def", &lexer));
 	printf("%i\n", word("#abc#|| def", &lexer));
	printf("Comment : %i\n", comment("#Hello world my name is ertuoll", &lexer));
	printf("Correct value : %i\n", strlen("#Hello world my name is ertuoll"));
	dump_tokens(&lexer);
	free(tokens);

}
*/
