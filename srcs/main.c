/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:12:12 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/16 18:42:34 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

char	*read_line(void)
{
	static char	*line_read = NULL;

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

void	clean(t_shell *shell)
{
	close(shell->stdio[0]);
	close(shell->stdio[1]);
	destroy_env(shell->env);
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	bool	break_flag;
	char	*line;
	t_shell	shell;

	(void)av;
	break_flag = true;
	if (ac != 1)
		exit(0);
	init_shell(&shell);
	parse_env(envp, &shell);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (break_flag)
	{
		line = read_line();
		if (parser_lexer(&shell, line))
			continue ;
		var_expansion(&shell);
		executor(&shell);
		destroy_cmd(shell.first_cmd);
		destroy_env_str(shell.env_str);
	}
	clean(&shell);
}
