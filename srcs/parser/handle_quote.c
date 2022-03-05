/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:49 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/05 15:38:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_var(char *str)
{
	int	i;

	i = 0;
	printf("%s\n", str);
	while (*str && *str != '$')
	{
		str++;
		i++;
	}
	if (*str == '$')
		return (i);
	return (-1);
}

int	get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

static	void	handle_quote_helper(\
		t_shell *shell, t_lexer *lexer, int *index, char **tmp)
{
	int		start_insert;
	char	*tmp2;
	char	*var;
	char	*tmp3;

	start_insert = check_var(lexer->tokens[*index].data);
	tmp2 = NULL;
	while (start_insert != -1)
	{
		tmp3 = ft_substr((*tmp) + start_insert, 0, get_end((*tmp) + start_insert));
		var = get_env_var(shell, tmp3);
		free(tmp3);
		(*tmp) = str_insert(*tmp, start_insert, get_end((*tmp) + start_insert), \
				var);
		free(var);
		if (tmp2)
			free(tmp2);
		start_insert = check_var(*tmp);
		tmp2 = (*tmp);
	}
}

void	handle_quote(t_shell *shell, t_lexer *lexer, t_cmd *current, int *index)
{
	char	*tmp;

	tmp = lexer->tokens[*index].data;
	if (lexer->tokens[*index].type == DQUOTE)
		handle_quote_helper(shell, lexer, index, &tmp);
	if (!current->cmd_name)
	{
		current->cmd_name = strdup(tmp);
		if (!current->cmd_name)
			printf("Error malloc\n");
	}
	if (append_cmd_args(tmp, current))
		exit(1);
	if (tmp != lexer->tokens[*index].data)
		free(tmp);
	(*index)++;
	return ;
}
