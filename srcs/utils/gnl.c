/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:08:19 by marvin            #+#    #+#             */
/*   Updated: 2022/03/04 18:21:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "libft.h"

static int	is_newline(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_substr_free(char *s, unsigned int start, size_t len, int free_s)
{
	size_t	tmp;
	char	*ret;

	if (s)
		tmp = ft_strlen((char *)s);
	if (!s || tmp < start)
	{
		ret = (char *)malloc(sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = 0;
		return (ret);
	}
	if (tmp < start + len)
		len = tmp - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	tmp = -1;
	while (++tmp < len)
		ret[tmp] = s[start + tmp];
	ret[tmp] = '\0';
	if (s && free_s)
		free(s);
	return (ret);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size_buffer;
	char	*ret;

	i = 0;
	j = 0;
	size_buffer = 1;
	if (s1)
		size_buffer += ft_strlen(s1);
	if (s2)
		size_buffer += ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * size_buffer);
	if (!ret)
		return (NULL);
	while (s1 && s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[j++] = s2[i++];
	ret[j] = '\0';
	if (s1)
		free(s1);
	return (ret);
}

static int	get_line(char **buf, char **line, int index_nl)
{
	if (index_nl == -1)
	{
		if (*buf)
			*line = *buf;
		else
		{
			*line = (char *)malloc(sizeof(char) * 1);
			if (!*line)
				return (GNL_ERROR);
			*line[0] = '\0';
		}
		*buf = NULL;
		return (0);
	}
	*line = ft_substr_free(*buf, 0, index_nl + NL, TO_KEEP);
	*buf = ft_substr_free(*buf, index_nl + 1,
			ft_strlen(*buf) - index_nl, TO_FREE);
	if (!*line || !*buf)
		return (GNL_ERROR);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int				index_nl;
	int				read_bytes;
	char			read_buffer[BUFFER_SIZE + 1];
	static char		*static_buffer[OPEN_MAX];

	read_bytes = 1;
	if (read(fd, 0, 0) < 0 || fd < 0 || !line || BUFFER_SIZE < 1)
		return (GNL_ERROR);
	index_nl = is_newline(static_buffer[fd]);
	while ((index_nl == -1) && (read_bytes))
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[read_bytes] = '\0';
		static_buffer[fd] = ft_strjoin_free(static_buffer[fd], read_buffer);
		if (!static_buffer[fd])
			return (GNL_ERROR);
		index_nl = is_newline(static_buffer[fd]);
	}
	return (get_line(&static_buffer[fd], line, index_nl));
}
