#include "shell.h"

void	destroy_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	t_cmd	*next;

	i = 0;
	next = cmd;
	while (next)
	{
		i++;
		j = 0;
		next = cmd->next;
		free(cmd->cmd_name);
		while (cmd->cmd_args && cmd->cmd_args[j])
		{
			free(cmd->cmd_args[j]);
			j++;
		}
		free(cmd->filename_in);
		free(cmd->filename_out);
		free(cmd->heredoc_end);
		free(cmd->cmd_args);
		free(cmd);
		cmd = next;
	}
}

/*
t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
*/

void	create_cmd(t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*last;

	new = (t_cmd *)calloc(1, sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		exit(1);
	}
	new->buffer_args = ARG_BUFFER_SIZE;
	if (!*cmd)
		*cmd = new;
	else
	{
		last = (*cmd);
		while (last->next)
			last = last->next;
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

static void	dump_cmds_(t_cmd *cmd)
{
	if (cmd->filename_in)
		printf("\n%s%s\n", "filename_in  : ", cmd->filename_in);
	else
		printf("\n%s%p\n", "filename_in  : ", cmd->filename_in);
	if (cmd->filename_in)
		printf("%s%s\n", "filename_out : ", cmd->filename_out);
	else
		printf("%s%s\n", "filename_out : ", cmd->filename_out);
	if (cmd->heredoc_end)
		printf("%s%s\n", "heredoc_end  : ", cmd->heredoc_end);
	else
		printf("%s%p\n", "heredoc_end  : ", cmd->heredoc_end);
	printf("fd_in : %i\n", cmd->fd_in);
	printf("fd_out : %i\n", cmd->fd_out);
}

void	dump_cmds(t_cmd *cmd)
{
	int		i;

	while (cmd)
	{
		i = 0;
		printf("------------------New command-----------------\n");
		if (cmd->cmd_name)
			printf("%s\n", cmd->cmd_name);
		else
			printf("%p\n", cmd->cmd_name);
		while (cmd->cmd_args && cmd->cmd_args[i])
		{
			printf("[%s]", cmd->cmd_args[i]);
			i++;
		}
		if (cmd->cmd_args)
			printf("\n");
		dump_cmds_(cmd);
		cmd = cmd->next;
	}
	printf("----------------------------------------------\n");
}
