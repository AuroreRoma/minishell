#include "shell.h"

/*
 *	TODO: handle_word check variable assignation
 *	TODO: handle_quote check variable expansion
 *
 */

/*
 *	handle_var search for the var and expand it i guess ?
 *
 */

static int	append_cmd_args(char *str, t_cmd *cmd)
{
	int		i;
	int		old_buffer;
	char	*new;

	i = 0;
	if (!cmd->cmd_args)
		cmd->cmd_args = (char **)calloc(cmd->buffer_args, sizeof(char *));
	if (!cmd->cmd_args)
		return (printf("Error malloc\n"));
	while (cmd->cmd_args[i])
		i++;
	if (i > cmd->buffer_args)
	{
		old_buffer = cmd->buffer_args;
		cmd->buffer_args += ARG_BUFFER_SIZE;
		cmd->cmd_args = (char **)calloc(cmd->buffer_args, sizeof(char *));
		if (!cmd->cmd_args)
			return (printf("Error malloc\n"));
		memset(cmd->cmd_args + old_buffer, 0, ARG_BUFFER_SIZE);
	}
	new = strdup(str);
	if (!new)
		return (printf("Error malloc\n"));
	cmd->cmd_args[i] = new;
	return (0);
}

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
 *
 *	handle quote
 *
 */

char	*str_insert(char *str, int start_insert, int end_insert, char *insert)
{
	char	*new;
	int		i;
	int		len_str;
	int		len_insert;

	len_str = strlen(str);
	len_insert = strlen(insert);
	new = (char *)malloc(sizeof(char) * (len_str + len_insert));
	if (!new)
		return (NULL);
	i = 0;
	while (i < start_insert)
	{
		new[i] = *str;
		str++;
		i++;
	}
	while (*insert)
	{
		new[i] = *insert;
		insert++;
		i++;
	}
	str += end_insert - start_insert + 1;
	while (*str)
	{
		new[i] = *str;
		str++;
		i++;
	}
	return (new);
}

int	check_var(char *str)
{
	int	i;

	i = 0;
	while (*str && *str != '$')
	{
		str++;
		i++;
	}
	return (i);
}

int main(void)
{
	char str[] = "Hello $VAR World";
	char rep[] = "42 21";

	printf("%i\n", check_var(str));
	printf("%s\n", str_insert(str, 6, 9, rep));
}

void	handle_quote(t_lexer *lexer, t_cmd *current, int *index)
{
	int		start_insert;
	char	*tmp;

	start_insert = check_var(lexer->tokens[*index].data);
	if (start_insert)
		tmp = 
	if (lexer->tokens[*index].type == QUOTE)
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
		return ;
	}
	// expand VAR_QUOTE
}
