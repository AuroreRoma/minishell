/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:48 by marvin            #+#    #+#             */
/*   Updated: 2022/03/18 17:58:04 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define DIRECTORY "Is a directory"
# define NOT_DIRECTORY "Not a directory"
# define NO_COMMAND "command not found"
# define NOT_FOUND "No such file or directory"
# define CORE_DUMP "Quit (core dumped)"
# define HERE_EOF1 ": warning: here-document at line "
# define HERE_EOF2 " delimited by end-of-file (wanted `"
# define HERE_EOF3 "')"

# define SYNTAX_ERROR "syntax error near unexpected token"
# define NL "newline"

int		error_lexer(t_lexer *lexer);
void	print_error_message_exec(char *name, char *string);
void	print_error_message_lexer(char *string, char *token);
void	print_error_message_heredoc(char *word, int line);
void	return_status_handler(t_shell *shell);

int		is_directory(char *filename);

#endif
