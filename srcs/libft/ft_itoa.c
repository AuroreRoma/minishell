/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:31:32 by pblagoje          #+#    #+#             */
/*   Updated: 2021/12/23 16:10:43 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_size(int n)
{
	int				size;
	unsigned int	num;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		num = -n;
		size++;
	}
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	int				size;
	unsigned int	num;

	i = 0;
	num = n;
	if (n < 0)
		num *= -1;
	size = ft_num_size(n);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[0] = '-';
	if (num == 0)
		res[0] = '0';
	while (num > 0)
	{
		res[size - 1 - i++] = num % 10 + 48;
		num /= 10;
	}
	res[size] = '\0';
	return (res);
}
