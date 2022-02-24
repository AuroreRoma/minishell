#include "shell.h"

/*
 *	TODO: var
 *	TODO: quote		// done
 *	TODO: heredoc
 *	TODO: norm
 *
 */

/*
 *
 *	count number of pipes for number of cmd
 *	cmd = pipe + 1
 *
 */

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
			handle_quote(lexer, current, &i);
		if (lexer->tokens[i].type == VAR)
			handle_word(lexer, current, &i);
		if (lexer->tokens[i].type == PIPE)
			handle_pipe(&current, &i);
	}
}

void	parser(t_lexer *lexer, t_shell *shell)
{
	int		nbr_of_cmds;
	t_cmd	*current;

	shell->first_cmd = NULL;
	printf("Number of tokens : %i\n", lexer->index);
	nbr_of_cmds = get_nbr_cmds(lexer);
	if (nbr_of_cmds < 0)
		return ;
	printf("Number of commands : %i\n", nbr_of_cmds);
	while (nbr_of_cmds--)
		create_cmd(&shell->first_cmd);
	current = shell->first_cmd;
	parse_token(lexer, shell);
	dump_cmds(current);
	destroy_cmd(shell->first_cmd);
}
