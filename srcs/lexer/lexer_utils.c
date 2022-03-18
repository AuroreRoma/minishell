/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:13:29 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 15:46:45 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int	comment(char *str, t_lexer *lexer)
{
	int	ret;

	ret = 1;
	if (str[0] != '#' || lexer->error)
		return (0);
	while (str[ret] && str[ret] != '\n')
		ret++;
	return (ret);
}

int	skip_space(char *str, t_lexer *lexer)
{
	int	ret;

	ret = 1;
	if (str[0] != ' ' || lexer->error)
		return (0);
	while (str[ret] && str[ret] == ' ')
		ret++;
	create_token(" ", 1, _SPACE, lexer);
	return (ret);
}
