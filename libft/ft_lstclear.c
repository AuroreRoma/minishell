/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:45:21 by pblagoje          #+#    #+#             */
/*   Updated: 2021/12/24 16:14:43 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*next;
	t_list	*rem;

	if (lst == NULL || del == NULL)
		return ;
	next = *lst;
	rem = NULL;
	while (next)
	{
		rem = next;
		next = next->next;
		ft_lstdelone(rem, del);
	}
	*lst = NULL;
}
