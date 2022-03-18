/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:49:22 by aroma             #+#    #+#             */
/*   Updated: 2022/03/18 10:44:25 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

char	*replace_var_(t_shell *shell, char *ptr, int *i)
{
	int		size_var;
	char	*old;
	char	*var;
	char	*var_value;

	size_var = get_end(ptr + *i);
	var = ft_substr(ptr, *i, size_var);
	var_value = get_env_var(shell, var);
	old = ptr;
	ptr = str_insert(old, *i, size_var, var_value);
	(*i) += ft_strlen(var_value);
	free(var);
	free(old);
	free(var_value);
	return (ptr);
}

void	var_expansion_cmd_args(t_shell *shell, t_cmd *cmd, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		var_replace_line(shell, &cmd_args[i]);
		if (!i)
		{
			free(cmd->cmd_name);
			cmd->cmd_name = ft_strdup(cmd_args[i]);
		}
		i++;
	}
}

// echo "$PWD"Hello'World'"'HIIIII'"

static void	la_norme_est_une_chose_magnifique(char *a, char *b, char c, char d)
{
	*a = c;
	*b = d;
}

void	var_replace_line(t_shell *shell, char **line)
{
	int		i;
	char	c;
	char	*ptr;

	ptr = (*line);
	i = 0;
	c = 0;
	while (ptr[i])
	{
		if (!c && (ptr[i] == '\'' || ptr[i] == '\"'))
		{
			la_norme_est_une_chose_magnifique(&c, &ptr[i], ptr[i], -1);
			i++;
		}
		else if (c == ptr[i])
			la_norme_est_une_chose_magnifique(&c, &ptr[i++], 0, -1);
		else if (c != '\'' && ptr[i] == '$')
		{
			ptr = replace_var_(shell, ptr, &i);
//			i++;
		}
		else
			i++;
	}
	(*line) = remove_quote_2_le_retour(ptr);
	free(ptr);
}
