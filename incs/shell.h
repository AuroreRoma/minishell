#ifndef SHELL_H
# define SHELL_H

# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOK_BUFFER_SIZE 64

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

/*		Lexer.c	typedef		*/

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;
typedef enum e_type		t_type;
typedef enum e_error	t_error;

/*
 *
 *
 *
 */

struct s_cmd
{
	char	*cmd_name;
	char	**cmd_args;
	int		fd_in;
	bool	to_close_in;
	int		fd_out;
	bool	to_close_out;
	t_cmd	*next;
};

struct s_shell
{
	t_cmd	*first_cmd;
	int		return_status;
};

void	parser(t_lexer *lexer, t_shell *shell);

/*
 *
 *	Lexer.c
 *
 */

enum e_type
{
	WORD = 1,
	NBR,
	PIPE,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	QUOTE,
	VAR,
	VAR_QUOTE
};

enum e_error
{
	no_error = 0,
	error_operator,
	error_quote
};

struct s_token
{
	t_type	type;
	char	*data;
};

struct	s_lexer
{
	int		buf_size;
	int		index;
	t_error	error;
	t_token	*tokens;
};

void	dump_tokens(t_lexer *lexer);
int		quote(char *str, t_lexer *lexer);
int		dollar(char *str, t_lexer *lexer, t_type type);
int		operator(char *str, t_lexer *lexer);
int		skip_space(char *str, t_lexer *lexer);
int		word(char *str, t_lexer *lexer);
int		comment(char *str, t_lexer *lexer);

void	handle_redirection(t_lexer *lexer, t_cmd **current, int *index);

#endif
