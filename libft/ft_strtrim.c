/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:52:26 by pblagoje          #+#    #+#             */
/*   Updated: 2021/12/23 16:22:22 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_is_charset(char const *set, char c)
{
	size_t		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		begin;
	size_t		end;
	size_t		pos;
	char		*res;

	begin = 0;
	pos = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_is_charset(set, s1[begin]))
		begin++;
	end = ft_strlen(s1);
	while (end > 0 && ft_is_charset(set, s1[end - 1]))
		end--;
	if (end == 0)
		begin = end;
	res = malloc(sizeof(char) * (end - begin + 1));
	if (!res)
		return (NULL);
	while (begin < end)
		res[pos++] = s1[begin++];
	res[pos] = '\0';
	return (res);
}
