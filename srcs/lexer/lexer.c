/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:13:21 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/05 15:51:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	quote_helper(char **start, char **str, char *quote, int *len)
{
	*start = *str;
	*quote = **str;
	*len = 1;
}

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
		len++;
		if (quote == '\'')
			create_token(str, len, QUOTE, lexer);
		else
			create_token(str, len, DQUOTE, lexer);
	}
	else if (str[len] != quote)
	{
		create_token(&quote, 1, ERROR, lexer);
		lexer->error = error_quote;
		return (0);
	}
	return ((str + len) - start);
}

int	dollar(char *str, t_lexer *lexer, t_type type)
{
	int		len_var;
	char	*start;

	start = str;
	if ((*str) != '$')
		return (0);
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
	{
		create_token(str, 2, ERROR, lexer);
		lexer->error = error_operator;
	}
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
