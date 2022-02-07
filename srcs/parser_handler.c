#include "shell.h"

/*
 *	handle_var search for the var and
 *
 */

void	handle_word(t_lexer *lexer, t_cmd **current, int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	current->cmd_name = lexer->tokens[*index].data;
	(*index)++;
	while (i < lexer->index)
	{
//		if ((!lexer->tokens[*index].type <= NBR))
//			break ;
		if (lexer->tokens[*index].type == NBR && \
				(lexer->tokens[*index + 1].type >= LESS && \
				 lexer->tokens[*index + 1].type <= DGREAT))
			break ;
		if (lexer->tokens[*index].type == VAR)
			handle_var();
		if (lexer->tokens[*index].type == QUOTE)
			tmp = handle_quote();
		curent->cmd_
	}
}
