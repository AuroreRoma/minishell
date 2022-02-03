#ifndef SHELL_H
# define SHELL_H

# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOK_BUFFER_SIZE 64 

typedef struct s_token	t_token;

struct s_token
{
	typedef enum	e_token
	{
		WORD = 1,
		PIPE,
		LESS,
		DLESS,
		GREAT,
		DGREAT,
		QUOTE,
		DQUOTE,
		VAR
	}	t_type;
	char			*data;
}

#endif
