/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:16:16 by wind              #+#    #+#             */
/*   Updated: 2022/03/17 22:15:31 by aroma            ###   ########.fr       */
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

int	is_redirection(t_type type)
{
	if (type == LESS || type == DLESS || type == GREAT || type == DGREAT)
		return (1);
	return (0);
}

int	is_arg(t_type type)
{
	if (type == WORD || type == QUOTE || type == DQUOTE \
		|| type == VAR || type == NBR)
		return (1);
	return (0);
}
