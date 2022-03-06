/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:42:33 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 13:36:09 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lstadd_back(t_env **alst, t_env *new)
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

void	add_env(char *var_line, t_shell *shell)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	t_env	*new;

	i = 0;
	j = 0;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	while (var_line[i] != '=')
		i++;
	key = ft_substr(var_line, 0, i);
	j = ft_strlen(var_line) - (i + 1);
	i++;
	value = ft_substr(var_line, i, j);
	new->env_full = ft_strdup(var_line);
	new->env_key = key;
	if (!ft_strcmp(value, ""))
		new->env_value = NULL;
	else
		new->env_value = value;
	new->next = NULL;
	lstadd_back(&shell->env, new);
}

void	parse_env(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		add_env(envp[i], shell);
		i++;
	}
}
