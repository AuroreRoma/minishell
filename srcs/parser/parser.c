/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:56 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 17:29:45 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

int	is_redirection(t_type type)
{
	if (type == LESS || type == DLESS || type == GREAT || type == DGREAT)
		return (1);
	return (0);
}

void	parse_token(t_lexer *lexer, t_shell *shell)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shell->first_cmd;
	while (i < lexer->index)
	{
		if (lexer->tokens[i].type == WORD)
			handle_word(lexer, current, &i);
		if (lexer->tokens[i].type == NBR)
		{
			if (is_redirection(lexer->tokens[i + 1].type))
				handle_redirection(lexer, current, &i);
			else
				handle_word(lexer, current, &i);
		}
		if (is_redirection(lexer->tokens[i].type))
			handle_redirection(lexer, current, &i);
		if (lexer->tokens[i].type == QUOTE || lexer->tokens[i].type == DQUOTE)
			handle_quote(shell, lexer, current, &i);
		if (lexer->tokens[i].type == VAR)
			handle_word(lexer, current, &i);
		if (lexer->tokens[i].type == PIPE)
			handle_pipe(&current, &i);
	}
}

int	parser(t_shell *shell, char *line)
{
	int		ret;
	int		nbr_of_cmds;
	t_lexer	lexer;

	ret = 1;
	tokenizer(&lexer, line);
	error_lexer(&lexer);
	if (!lexer.error && lexer.index)
	{
		ret = 0;
		shell->first_cmd = NULL;
		nbr_of_cmds = get_nbr_cmds(&lexer);
		shell->nbr_cmd = nbr_of_cmds;
		if (nbr_of_cmds < 0)
			ret = 1;
		while (nbr_of_cmds--)
			create_cmd(&shell->first_cmd);
		parse_token(&lexer, shell);
	}
	destroy_tokens(&lexer, lexer.tokens);
	return (ret);
}
