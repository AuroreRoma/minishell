/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 14:51:51 by marvin            #+#    #+#             */
/*   Updated: 2022/03/05 15:43:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

/*

DONE: func 1 : search key in linked list

TODO: func 2 : search through cmd_args for $
				// strdup the value of the var instead of the $
				// free the $ cmd_args
TODO: func 3 : search through redirections for $
				// strdup the value of the var instead of the $
				// free the $ data in redirections
				// if heredoc func 4
TODO: func 4 : get_next_line on heredoc_file
				// scan each line for a $
				// replace it with str_insert
				// dump into new file
TODO: func 5 : call func 2
				// call func 3

*/

char	*get_env_var(t_shell *shell, char *str)
{
	char	*var;
	t_env	*current;

	if (!((*str) + 1 == '{'))
		var = ft_strdup(str + 1);
	else
		var = ft_substr(str + 2, 0, ft_strlen(str) - 3);
	current = shell->envv;
	while (current)
	{
		if (!ft_strcmp(current->envv_key, var))
		{
			if (current->envv_value)
			{
				free(var);
				return (ft_strdup(current->envv_value));
			}
			break ;
		}
		current = current->next;
	}
	free(var);
	return (ft_strdup(""));
}
