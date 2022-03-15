/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:48 by marvin            #+#    #+#             */
/*   Updated: 2022/03/15 18:49:27 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define DIRECTORY "Is a directory"
# define NO_COMMAND "command not found"

# define SYNTAX_ERROR "syntax error near unexpected token"
# define NL "newline"

int		error_lexer(t_lexer *lexer);
void	print_error_message_exec(char *name, char *string);
void	print_error_message_lexer(char *string, char *token);
void	print_error_message(char *cmd_name, char *string);
int		return_status_handler(int wstatus);

int		is_directory(char *filename);

#endif
