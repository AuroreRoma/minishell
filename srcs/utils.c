#include "shell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n && src[i] != '\0')
		dest[i] = src[i];
//	while (i++ < n)
		dest[i] = '\0';
	printf("DEBUG\n%s\n%s\n", dest, src);
	return (dest);
}

char	*str_insert(char *str, int start_insert, int size_insert, char *insert)
{
    char	*new;
    int		i;
    int		len_str;
    int		len_insert;

	len_str = strlen(str);
	len_insert = strlen(insert);
	new = (char *)malloc(sizeof(char) * (len_str + len_insert) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < start_insert)
	{
		new[i] = *str;
		str++;
		i++;
	}
//	new = ft_strncpy(new, str, start_insert - 1);
//	i += start_insert;
//	str += start_insert;
	while (*insert)
	{
		new[i] = *insert;
		insert++;
		i++;
	}
	str += size_insert;
	while (*str)
	{
		new[i] = *str;
		str++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
