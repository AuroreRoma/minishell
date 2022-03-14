/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:12:12 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 15:16:57 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

void	destroy_tokens(t_lexer *lexer, t_token *tokens)
{
	int	i;

	i = -1;
	while (++i != lexer->index)
		free(tokens[i].data);
	free(tokens);
}

void	*tokenizer(t_lexer *lexer, char *str)
{
	lexer->error = no_error;
	lexer->index = 0;
	lexer->buf_size = TOK_BUFFER_SIZE;
	lexer->tokens = (t_token *)ft_calloc(TOK_BUFFER_SIZE, sizeof(t_token));
	if (!lexer->tokens)
		return (NULL);
	while (str && *str && !lexer->error)
	{
		str += quote(str, lexer);
		str += dollar(str, lexer, VAR);
		str += operator(str, lexer);
		str += skip_space(str, lexer);
		str += word(str, lexer);
		str += comment(str, lexer);
	}
	return (NULL);
}

int	is_reading_line(int flag)
{
	static int	n = 0;

	if (flag >= 0)
		n = flag;
	return (n);
}

char	*read_line(void)
{
	static char	*line_read = NULL;

	is_reading_line(1);
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("$> ");
	if (line_read && *line_read)
		add_history(line_read);
	else if (line_read == NULL)
	{
		printf("exit\n");
		free(line_read);
		exit(0);
	}
	is_reading_line(0);
	return (line_read);
}

void	init_shell(t_shell *shell)
{
	shell->first_cmd = NULL;
	shell->env = NULL;
	shell->env_str = NULL;
	shell->return_status = 0;
	shell->nbr_cmd = 0;
	shell->stdio[0] = dup(0);
	shell->stdio[1] = dup(1);
}

int	main(int ac, char **av, char **envp)
{
	bool	break_flag;
	char	*line;
	t_lexer	lexer;
	t_shell	shell;

	(void)av;
	break_flag = true;
	if (ac != 1)
		exit(0);
	init_shell(&shell);
	parse_env(envp, &shell);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	while (break_flag)
	{
		line = read_line();
		tokenizer(&lexer, line);
		error_lexer(&lexer);
		if (!lexer.error && lexer.index)
		{
			parser(&lexer, &shell);
//			dump_cmds(shell.first_cmd);
			var_expansion(&shell);
			executor(&shell);
			destroy_cmd(shell.first_cmd);
		}
		destroy_tokens(&lexer, lexer.tokens);
		destroy_env_str(shell.env_str);
	}
	close(shell.stdio[0]);
	close(shell.stdio[1]);
	destroy_env(shell.env);
	rl_clear_history();
}
