/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:06 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 12:32:24 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n && src[i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*str_insert(char *str, int start_insert, int size_insert, char *insert)
{
	char	*new;
	int		i;
	int		len_str;
	int		len_insert;

	len_str = ft_strlen(str);
	len_insert = ft_strlen(insert);
	new = (char *)malloc(sizeof(char) * (len_str + len_insert) + 1);
	if (!new)
		return (NULL);
	i = 0;
	new = ft_strncpy(new, str, start_insert);
	i += start_insert;
	str += start_insert;
	ft_strncpy(new + i, insert, len_insert);
	i += len_insert;
	str += size_insert;
	ft_strncpy(new + i, str, len_str);
	return (new);
}
