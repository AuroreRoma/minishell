/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:42:33 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/03 17:03:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

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
	new->envv_full = var_line;
	new->envv_key = key;
	if (!ft_strcmp(value, ""))
		new->envv_value = NULL;
	else
		new->envv_value = value;
	new->next = NULL;
	ft_lstadd_back(&shell->envv, new);
}

void	print_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->envv;
	while (tmp->next != NULL)
	{
		printf("Key: %s\nValue: %s\n\n", tmp->envv_key, tmp->envv_value);
		tmp = tmp->next;
	}
}

void	parse_env(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_env(envp[i], shell);
		i++;
	}
	print_env(shell);
}
