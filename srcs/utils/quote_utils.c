/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:48:45 by aroma             #+#    #+#             */
/*   Updated: 2022/03/17 22:09:57 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 *	Parse string and remove quote
 */

char	*remove_quote_2_le_retour(char *string)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (string[j])
		j++;
	ret = malloc(sizeof(char) * (j + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (string[i])
	{
		if (string[i] == -1)
			i++;
		else
			ret[j++] = string[i++];
	}
	ret[j] = '\0';
	return (ret);
}

char	*remove_quote(char *string)
{
	int		i;
	int		j;
	char	buf;
	char	*ret;

	i = 0;
	j = 0;
	buf = -1;
	while (string[j])
		j++;
	ret = malloc(sizeof(char) * (j + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (string[i])
	{
		if (buf == -1 && (string[i] == '\'' || string[i] == '\"'))
			buf = string[i++];
		else if (buf == string[i] && i++)
			buf = -1;
		else
			ret[j++] = string[i++];
	}
	ret[j] = '\0';
	return (ret);
}
