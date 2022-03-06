/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:58:17 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 13:52:57 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	count_env(t_shell *shell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = shell->env;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_to_str(t_shell *shell)
{
	int		i;
	int		env_number;
	char	**str;
	t_env	*tmp;

	i = 0;
	tmp = shell->env;
	env_number = count_env(shell);
	str = (char **)ft_calloc(env_number + 1, sizeof(char *));
	while (i < env_number)
	{
		str[i] = tmp->env_full;
		tmp = tmp->next;
		i++;
	}
	return (str);
}
