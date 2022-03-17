/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 14:51:51 by marvin            #+#    #+#             */
/*   Updated: 2022/03/17 22:07:04 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "gnl.h"

/*

DONE: func 1 : search key in linked list

DONE: func 2 : search through cmd_args for $
				// strdup the value of the var instead of the $
				// free the $ cmd_args
DONE: func 3 : search through redirections for $
				// strdup the value of the var instead of the $
				// free the $ data in redirections
				// if heredoc func 4
TODO: func 4 : get_next_line on heredoc_file
				// scan each line for a $
				// replace it with str_insert
				// dump into new file
DONE: func 5 : call func 2
				// call func 3

*/

char	*get_env_var(t_shell *shell, char *str)
{
	char	*var;
	t_env	*current;

	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(shell->return_status));
	if (*(str + 1) != '{')
		var = ft_strdup(str + 1);
	else
		var = ft_substr(str + 2, 0, ft_strlen(str) - 3);
	current = shell->env;
	while (current)
	{
		if (!ft_strcmp(current->env_key, var))
		{
			if (current->env_value)
			{
				free(var);
				return (ft_strdup(current->env_value));
			}
			break ;
		}
		current = current->next;
	}
	free(var);
	return (ft_strdup(""));
}

void	replace_var(t_shell *shell, char **ptr)
{
	char	*old;

	if (**ptr == '$')
	{
		old = *ptr;
		*ptr = get_env_var(shell, old);
		free(old);
	}
}

void	search_and_replace_var(t_shell *shell, char **line)
{
	int		start_insert;
	int		size_var;
	char	*var;
	char	*var_value;
	char	*old_line;

	start_insert = check_var(*line);
	while (start_insert != -1)
	{
		size_var = get_end((*line) + start_insert);
		var = ft_substr((*line) + start_insert, 0, size_var);
		var_value = get_env_var(shell, var);
		old_line = *line;
		(*line) = str_insert(old_line, start_insert, size_var, var_value);
		free(var);
		free(old_line);
		free(var_value);
		start_insert = check_var(*line);
	}
}

void	var_expansion(t_shell *shell)
{
	t_cmd	*current;

	current = shell->first_cmd;
	while (current)
	{
		if (current->cmd_args)
			var_expansion_cmd_args(shell, current, current->cmd_args);
		var_expansion_redirection(shell, current->redirection);
		current = current->next;
	}
}
