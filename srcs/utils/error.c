/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:21:33 by wind              #+#    #+#             */
/*   Updated: 2022/03/18 17:57:23 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

int	is_directory(char *filename)
{
	struct stat	st;

	if (lstat(filename, &st) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	print_error_message_heredoc(char *word, int line)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(HERE_EOF1, 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(HERE_EOF2, 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd(HERE_EOF3, 2);
}

void	print_error_message_exec(char *name, char *string)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(string, 2);
}

void	print_error_message_lexer(char *string, char *token)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	return_status_handler(t_shell *shell)
{
	if (shell->return_status)
		return ;
	if (WIFEXITED(shell->wstatus))
		shell->return_status = WEXITSTATUS(shell->wstatus);
	if (WIFSIGNALED(shell->wstatus))
	{
		shell->return_status = 128;
		shell->return_status += WTERMSIG(shell->wstatus);
	}
}
