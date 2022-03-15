/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:16:16 by wind              #+#    #+#             */
/*   Updated: 2022/03/15 18:23:28 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*generate_herefile_name(void)
{
	char		*str;
	char		*ret;
	static int	n_file = 0;

	n_file++;
	if ((n_file) == 32)
		n_file = 0;
	ret = ft_itoa(n_file);
	str = ft_strjoin(".herefile_", ret);
	free(ret);
	ret = ft_strjoin(str, ".tmp");
	free(str);
	return (ret);
}
