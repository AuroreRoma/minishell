/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:56:23 by pblagoje          #+#    #+#             */
/*   Updated: 2021/12/23 16:22:41 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[start + i] && i < (unsigned int)len)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res[0] = '\0';
		return (res);
	}
	while (j < i)
	{
		res[j] = s[start + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}
