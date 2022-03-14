/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:48 by marvin            #+#    #+#             */
/*   Updated: 2022/03/14 19:06:53 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNTAX_ERROR "syntax error near unexpected token"
# define NL "newline"

void	error_lexer(t_lexer *lexer);
void	print_error_message_lexer(char *string, char *token);
void	print_error_message(char *cmd_name, char *string);
int		return_status_handler(int wstatus);

#endif
