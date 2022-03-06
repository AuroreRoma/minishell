/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:46:32 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 14:41:45 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*s2;
	size_t	len_s1;
	size_t	i;

	len_s1 = 0;
	i = 0;
	while (s1[len_s1] && len_s1 < size)
		len_s1++;
	s2 = malloc(sizeof(char) * len_s1 + 1);
	if (!s2)
		return (NULL);
	while (s1[i] && i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
