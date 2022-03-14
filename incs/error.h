/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:48 by marvin            #+#    #+#             */
/*   Updated: 2022/03/14 15:19:40 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNTAX_ERROR "syntax error near unexpected token"
# define NL "newline"

# define CORE_DUMPED "Quit (core dumped)"

void	error_lexer(t_lexer *lexer);

#endif
