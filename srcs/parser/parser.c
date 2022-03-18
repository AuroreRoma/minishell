/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:14:56 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 15:53:57 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	join_token(t_lexer *lexer, int *index)
{
	int		i;
	char	*ptr;
	char	*str;

	i = *index;
	if (lexer->tokens[i].type == _SPACE)
		i++;
	ptr = NULL;
	str = ft_strdup(lexer->tokens[i].data);
	i++;
	while (i < lexer->index && lexer->tokens[i].type != _SPACE && \
		lexer->tokens[i].type != PIPE && !is_redirection(lexer->tokens[i].type))
	{
		ptr = ft_strjoin(str, lexer->tokens[i].data);
		free(str);
		str = ptr;
		i++;
	}
	(*index) = i - 1;
	free(lexer->tokens[i - 1].data);
	lexer->tokens[i - 1].data = str;
	lexer->tokens[i - 1].type = WORD;
}

void	parse_token(t_lexer *lexer, t_shell *shell)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = shell->first_cmd;
	while (i < lexer->index)
	{
		if (lexer->tokens[i].type == NBR && \
				is_redirection(lexer->tokens[i + 1].type))
			handle_redirection(shell, lexer, current, &i);
		if (is_arg(lexer->tokens[i].type))
			join_token(lexer, &i);
		if (lexer->tokens[i].type == NBR || lexer->tokens[i].type == WORD)
			handle_word(lexer, current, ft_strdup(lexer->tokens[i].data), &i);
		if (is_redirection(lexer->tokens[i].type))
			handle_redirection(shell, lexer, current, &i);
		if (lexer->tokens[i].type == PIPE)
			handle_pipe(&current, &i);
		if (lexer->tokens[i].type == _SPACE)
			i++;
	}
}
// [WORD || QUOTE || DQUOTE || VAR] [PIPE || _SPACE || REDIRECTIONS] [...]

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
