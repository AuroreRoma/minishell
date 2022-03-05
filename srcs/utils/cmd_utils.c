/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:13:50 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/05 16:33:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	__ft_lstclear(t_red **lst)
{
	t_red	*next;
	t_red	*rem;

	if (lst == NULL)
		return ;
	next = *lst;
	rem = NULL;
	while (next)
	{
		rem = next;
		next = next->next;
		free(rem->data);
		free(rem);
	}
	*lst = NULL;
}

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
		__ft_lstclear(&cmd->redirection);
		free(cmd->cmd_args);
		free(cmd);
		cmd = next;
	}
}

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
	new->buffer_size = ARG_BUFFER_SIZE;
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

void	dump_cmds(t_cmd *cmd)
{
	int		i;
	t_red	*next;

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
		i = 0;
		next = cmd->redirection;
		while (next)
		{
			printf("Redirection %i : type %i : %s\n", i, next->type, next->data);
			next = next->next;
			i++;
		}
		cmd = cmd->next;
	}
	printf("----------------------------------------------\n");
}
