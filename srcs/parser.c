#include "shell.h"

/*
 *
 *	count number of pipes for number of cmd
 *	cmd = pipe + 1
 *
 */

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}


void	destroy_cmd(t_cmd *cmd)
{
	t_cmd	*next;
	int i;

	i = 0;
	next = cmd;
	while (next)
	{
		i++;
		next = cmd->next;
		/*
		 *	free bunch of stuff;
		 */
		free(cmd);
		cmd = next;
	}
}

void	create_cmd(t_cmd **cmd)
{
	t_cmd *new;
	t_cmd *last;

	new = (t_cmd *)calloc(1, sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		exit(1);
	}
	if (!*cmd)
		*cmd = new;
	else
	{
		last = get_last_cmd(*cmd);
		last->next = new;
	}
}

int	get_nbr_cmds(t_lexer *lexer)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (i < lexer->index)
	{
		if (lexer->tokens[i].type == PIPE)
			ret++;
		i++;
	}
	if (lexer->tokens[lexer->index - 1].type == PIPE)
	{
		printf("Error w/ pipe\n");
		return (-1);
	}
	return (ret);
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
			handle_word();
		if (lexer->tokens[i].type == NBR)
		{
			if (lexer->tokens[i + 1].type == LESS || \
					lexer->tokens[i + 1].type == DLESS || \
					lexer->tokens[i + 1].type == GREAT || \
					lexer->tokens[i + 1].type == DGREAT)
				handle_redirections();
			else
				handle_word();
		}
		if (lexer->tokens[i].type == LESS || lexer->tokens[i].type == DLESS || \
			lexer->tokens[i].type == GREAT || lexer->tokens[i].type == DGREAT)
			handle_redirections();
		if (lexer->tokens[i].type == QUOTE || \
			lexer->tokens[i].type == VAR_QUOTE)
			handle_quote();
		if (lexer->tokens[i].type == VAR)
			handle_var();
		i++;
	}
}

void	parser(t_lexer *lexer, t_shell *shell)
{
	int		nbr_of_cmds;

	shell->first_cmd = NULL;
	printf("Number of tokens : %i\n", lexer->index);
	nbr_of_cmds = get_nbr_cmds(lexer);
	if (nbr_of_cmds < 0)
		return ;
	printf("Number of commands : %i\n", nbr_of_cmds);
	while (nbr_of_cmds--)
		create_cmd(&shell->first_cmd);
//	parse_token(lexer, shell);
	destroy_cmd(shell->first_cmd);
}
