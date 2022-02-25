/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:13:33 by pblagoje          #+#    #+#             */
/*   Updated: 2022/02/24 22:36:18 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)mem)[i] = '\0';
		i++;
	}
	return (mem);
}
