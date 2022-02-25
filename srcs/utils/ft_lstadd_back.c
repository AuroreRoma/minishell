/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:57:06 by pblagoje          #+#    #+#             */
/*   Updated: 2022/02/24 23:04:56 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*current;

	if (*alst == NULL)
		*alst = new;
	else
	{
		current = *alst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
