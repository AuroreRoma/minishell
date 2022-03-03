/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:05:36 by marvin            #+#    #+#             */
/*   Updated: 2022/03/03 18:17:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	destroy_env(t_env *head)
{
	t_env	*next;

	next = head;
	while (next)
	{
		next = next->next;
		if (head->envv_key)
			free(head->envv_key);
		if (head->envv_value)
			free(head->envv_value);
		free(head);
		head = next;
	}
}
