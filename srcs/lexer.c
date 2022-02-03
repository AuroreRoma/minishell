#include "shell.h"

int	quote(char *str, t_token **tokens, int *buf_size)
{
	char	tmp;

	if (!(*str == '\'' || *str == '\"'))
		return (0);
	
}


