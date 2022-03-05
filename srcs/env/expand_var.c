/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 14:51:51 by marvin            #+#    #+#             */
/*   Updated: 2022/03/05 17:33:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

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

void	placeholder_function_name(t_shell *shell, char **ptr)
{
	char	*old;

	if (**ptr == '$')
	{
		old = *ptr;
		*ptr = get_env_var(shell, old);
		free(old);
	}
	else if (**ptr == '\'' || **ptr == '\"')
	{
		old = *ptr;
		*ptr = ft_substr(old + 1, 0, ft_strlen(old) - 2);
		free(old);
	}
}

void	var_expansion_cmd_args(t_shell *shell, t_cmd *cmd, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		placeholder_function_name(shell, &cmd_args[i]);
		if (!i)
		{
			free(cmd->cmd_name);
			cmd->cmd_name = ft_strdup(cmd_args[i]);
		}
		i++;
	}
}


void	var_expansion_heredoc()
{
	;
}

void	var_expansion_redirection(t_shell *shell, t_red *current)
{
	while (current)
	{
		placeholder_function_name(shell, &current->data);
		if (current->type == redir_heredoc)
			var_expansion_heredoc();
		current = current->next;
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
