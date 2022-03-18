/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:49:53 by aroma             #+#    #+#             */
/*   Updated: 2022/03/18 15:38:33 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_len, size_t new_len, size_t size)
{
	void	*ret;

	if (!ptr)
		return (malloc(new_len * size));
	else if (new_len <= old_len)
		return (ptr);
	else
	{
		if (!ptr || new_len < old_len)
			return (NULL);
		ret = malloc(new_len * size);
		if (ret)
		{
			ft_memcpy(ret, ptr, old_len * size);
			free(ptr);
		}
		return (ret);
	}
}
