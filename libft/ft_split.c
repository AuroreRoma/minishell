/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:09:42 by pblagoje          #+#    #+#             */
/*   Updated: 2022/01/07 17:28:32 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sep(char let, char c)
{
	if (let == c)
		return (1);
	return (0);
}

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		is_word;
	int		word_count;

	i = 0;
	is_word = 0;
	word_count = 0;
	while (s[i])
	{
		if (ft_is_sep(s[i], c))
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

static int	ft_wd(char const *s, char c, int pos)
{
	int		count;

	count = 0;
	while (s[pos])
	{
		if (!ft_is_sep(s[pos], c))
			count++;
		pos++;
	}
	return (count);
}

static void	ft_splitter(char const *s, char c, char **res)
{
	int		pos;
	int		i;
	int		j;

	pos = 0;
	i = 0;
	j = 0;
	while (s[pos])
	{
		if (!ft_is_sep(s[pos], c))
		{
			if (j == 0)
				res[i] = malloc(sizeof(char) * ft_wd(s, c, pos) + 1);
			res[i][j] = s[pos];
			res[i][j + 1] = '\0';
			j++;
		}
		if (ft_is_sep(s[pos], c) && !ft_is_sep(s[pos + 1], c)
			&& j > 0)
		{
			i++;
			j = 0;
		}
		pos++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!res)
		return (NULL);
	ft_splitter(s, c, res);
	res[ft_count_words(s, c)] = NULL;
	return (res);
}
