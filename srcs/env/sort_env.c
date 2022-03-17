/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:14:57 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/16 19:48:54 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	env_compare(t_env *first, t_env *second)
{
	int	i;

	i = 0;
	while (first->env_key[i])
	{
		if (first->env_key[i] > second->env_key[i])
			return (1);
		else if (first->env_key[i] < second->env_key[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

t_env	*env_find_first(t_shell *shell)
{
	t_env	*first;
	t_env	*tmp;

	first = shell->env;
	tmp = shell->env;
	while (tmp)
	{
		if (env_compare(tmp, first) <= 0)
			first = tmp;
		tmp = tmp->next;
	}
	return (first);
}

t_env	*env_find_last(t_shell *shell)
{
	t_env	*last;
	t_env	*tmp;

	last = shell->env;
	tmp = shell->env;
	while (tmp)
	{
		if (env_compare(tmp, last) > 0)
			last = tmp;
		tmp = tmp->next;
	}
	return (last);
}

t_env	*env_find_next(t_shell *shell, t_env *current)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->env;
	new = env_find_last(shell);
	while (tmp)
	{
		if (env_compare(tmp, new) <= 0 && \
			env_compare(tmp, current) > 0 && \
			ft_strcmp(tmp->env_key, "_"))
			new = tmp;
		tmp = tmp->next;
	}
	return (new);
}

void	sort_env(t_shell *shell)
{
	t_env	*current;
	t_env	*tmp;
	t_env	*new;
	int		i;

	i = 0;
	tmp = shell->env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	current = env_find_first(shell);
	shell->env_sorted = current;
	while (i > 0)
	{
		new = env_find_next(shell, current);
		current->sorted_next = new;
		current = current->sorted_next;
		i--;
	}
	current->sorted_next = NULL;
}
