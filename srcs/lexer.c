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

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	size_var(char *str, char tmp)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != tmp && str[i] && \
			!is_operator(str[i]) && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	return (i);
}

static void	quote_helper(char **start, char **str, char *quote, int *len)
{
	*start = *str;
	*quote = **str;
	(*str)++;
	*len = 0;
}

int	quote(char *str, t_lexer *lexer)
{
	int		len;
	char	quote;
	char	*start;
//	int		len_var;

	if (!(*str == '\'' || *str == '\"'))
		return (0);
	quote_helper(&start, &str, &quote, &len);
	while (str[len] && str[len] != quote)
	{
		if (quote == '\"' && str[len] == '$')
		{
			create_token(str, len, QUOTE, lexer);
			str += len + dollar(str + len, lexer, VAR_QUOTE);
//			len_var = size_var(str + len, quote);
//			create_token(str, len, VAR, lexer);
//			str += len + len_var;
			len = 0;
		}
		else
			len++;
	}
	if (str[len] == quote)
		create_token(str, len, QUOTE, lexer);
	else
		lexer->error = error_quote;
	return ((str + len + 1) - start);
}

int	dollar(char *str, t_lexer *lexer, t_type type)
{
	int		len_var;
	char	*start;

	start = str;
	if (!((*str) == '$'))
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

int	is_number(char *str, int len)
{
	int	i;

	i = 0;
	while (i != len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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

int	comment(char *str, t_lexer *lexer)
{
	int	ret;

	ret = 1;
	(void)lexer;
	if (str[0] != '#')
		return (0);
	while (str[ret] && str[ret] != '\n')
		ret++;
	return (ret);
}

int	skip_space(char *str, t_lexer *lexer)
{
	int	ret;

	ret = 1;
	(void)lexer;
	if (str[0] != ' ')
		return (0);
	while (str[ret] && str[ret] == ' ')
		ret++;
	return (ret);
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
