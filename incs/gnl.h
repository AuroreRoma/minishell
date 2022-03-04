/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:41 by marvin            #+#    #+#             */
/*   Updated: 2022/03/04 18:22:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

# define TO_FREE 1
# define TO_KEEP 0
# define GNL_ERROR -1

# ifndef OPEN_MAX
#  define OPEN_MAX FOPEN_MAX
# endif

# define NL 1

// if NL == 1, line is returned with \n
// if NL == 0, line is returned without \n

int		get_next_line(const int fd, char **line);

#endif
