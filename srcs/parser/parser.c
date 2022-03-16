/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:56 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/16 18:42:36 by aroma            ###   ########.fr       */
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
				handle_redirection(shell, lexer, current, &i);
			else
				handle_word(lexer, current, &i);
		}
		if (is_redirection(lexer->tokens[i].type))
			handle_redirection(shell, lexer, current, &i);
		if (lexer->tokens[i].type == QUOTE || lexer->tokens[i].type == DQUOTE)
			handle_quote(shell, lexer, current, &i);
		if (lexer->tokens[i].type == VAR)
			handle_word(lexer, current, &i);
		if (lexer->tokens[i].type == PIPE)
			handle_pipe(&current, &i);
	}
}

static int	parser(t_shell *shell, t_lexer *lexer)
{
	int	nbr_of_cmds;

	shell->first_cmd = NULL;
	nbr_of_cmds = get_nbr_cmds(lexer);
	shell->nbr_cmd = nbr_of_cmds;
	if (nbr_of_cmds < 0)
		return (1);
	while (nbr_of_cmds--)
		create_cmd(&shell->first_cmd);
	parse_token(lexer, shell);
	if (!lexer->error)
		return (0);
	destroy_cmd(shell->first_cmd);
	return (1);
}

int	parser_lexer(t_shell *shell, char *line)
{
	int		ret;
	t_lexer	lexer;

	ret = 1;
	tokenizer(&lexer, line);
	if (error_lexer(&lexer))
		shell->return_status = 2;
	if (!lexer.error && lexer.index)
		ret = parser(shell, &lexer);
	destroy_tokens(&lexer, lexer.tokens);
	return (ret);
}
