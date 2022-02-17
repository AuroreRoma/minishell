#include "shell.h"

/*
 *	handle_var search for the var and
 *
 */
/*
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
*/

/*
 *	([NBR]) [REDIREC] [WORD]
 *
 */


void	handle_redirection(t_lexer *lexer, t_cmd **current, int *index)
{
	if (lexer->tokens[*index].type == NBR && \
			(lexer->tokens[*index + 1].type == LESS || \
			 lexer->tokens[*index + 1].type == DLESS))
		(*current)->fd_in = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR && \
			(lexer->tokens[*index + 1].type == GREAT || \
			 lexer->tokens[*index + 1].type == DGREAT))
		(*current)->fd_out = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR)
		(*index) += 1;
	else if (lexer->tokens[*index].type == LESS || \
			lexer->tokens[*index].type == DLESS)
		(*current)->fd_in = atoi(lexer->tokens[*index].data);
	else if (lexer->tokens[*index].type == GREAT || \
			lexer->tokens[*index].type == DGREAT)
		(*current)->fd_out = atoi(lexer->tokens[*index].data);
	else
		printf("Error\n");
	(*index) += 1;
	if (lexer->tokens[*index].type == WORD)
		; // open file corresponding to word path
	else
		printf("\x1B[31mshell: parse error near `%s'\x1B[0m\n", \
				lexer->tokens[*index].data);
	// raise error
	(*index) += 1;
}
