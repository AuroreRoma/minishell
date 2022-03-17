/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:15:04 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/17 17:18:22 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	handle_pipe(t_cmd **current, int *index)
{
	(*current) = (*current)->next;
	(*index)++;
}

void	handle_word(t_lexer *lexer, t_cmd *current, char *str, int *index)
{
	if (!current->cmd_name)
	{
		current->cmd_name = ft_strdup(str);
		if (!current->cmd_name)
			printf("Error malloc\n");
	}
	if (append_cmd_args(str, current))
		lexer->error = error_malloc;
	free(str);
	(*index)++;
}
