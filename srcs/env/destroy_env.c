/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:05:36 by marvin            #+#    #+#             */
/*   Updated: 2022/03/06 14:04:45 by pblagoje         ###   ########.fr       */
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
		if (head->env_full)
			free(head->env_full);
		if (head->env_key)
			free(head->env_key);
		if (head->env_value)
			free(head->env_value);
		free(head);
		head = next;
	}
}
