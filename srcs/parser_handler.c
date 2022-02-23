#include "shell.h"

/*
 *	TODO: handle_word check variable assignation // exec
 *	TODO: handle_quote check variable expansion // done
 *
 */

/*
 *	handle_var search for the var and expand it i guess ?
 *
 */

void	handle_word(t_lexer *lexer, t_cmd *current, int *index)
{
	if (!current->cmd_name)
	{
		current->cmd_name = strdup(lexer->tokens[*index].data);
		if (!current->cmd_name)
			printf("Error malloc\n");
	}
	if (append_cmd_args(lexer->tokens[*index].data, current))
		exit(1);
	(*index)++;
}


/*
 *	([NBR]) [REDIREC] [WORD]
 *
 */


void	handle_redirection(t_lexer *lexer, t_cmd *current, int *index)
{
	if (lexer->tokens[*index].type == NBR && \
			(lexer->tokens[*index + 1].type == LESS || \
			 lexer->tokens[*index + 1].type == DLESS))
		current->fd_out = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR && \
			(lexer->tokens[*index + 1].type == GREAT || \
			 lexer->tokens[*index + 1].type == DGREAT))
		current->fd_in = atoi(lexer->tokens[*index].data);
	if (lexer->tokens[*index].type == NBR)
		(*index) += 1;
	else if (lexer->tokens[*index].type == LESS || \
			lexer->tokens[*index].type == DLESS)
		current->fd_out = 1;
	else if (lexer->tokens[*index].type == GREAT || \
			lexer->tokens[*index].type == DGREAT)
		current->fd_in = 0;
	else
		printf("Error\n");
	(*index) += 1;
	if (lexer->tokens[*index].type == WORD)
	{
		if (lexer->tokens[*index - 1].type == GREAT || \
				lexer->tokens[*index - 1].type == DGREAT)
			current->filename_out = strdup(lexer->tokens[*index].data);
		else if (lexer->tokens[*index - 1].type == LESS)
			current->filename_in = strdup(lexer->tokens[*index].data);
		else
			current->heredoc_end = strdup(lexer->tokens[*index].data);
	}
	else
		printf("\x1B[31mshell: parse error near `%s'\x1B[0m\n", \
				lexer->tokens[*index].data);
	// raise error
	(*index) += 1;
}

/*

   if (DQUOTE)
   while (check ($))
   if $
   expand
   else
   break
   append
   */
