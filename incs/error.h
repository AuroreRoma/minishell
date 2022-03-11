/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:48 by marvin            #+#    #+#             */
/*   Updated: 2022/03/11 15:53:37 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNTAX_ERROR "syntax error near unexpected token"
# define NL "newline"

void	error_lexer(t_lexer *lexer);

#endif
