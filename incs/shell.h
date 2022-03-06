/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:11:30 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/06 13:54:29 by pblagoje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h"

# define TOK_BUFFER_SIZE 64
# define ARG_BUFFER_SIZE 32
# define RED_BUFFER_SIZE 16

# define SHELL_NAME "minishell"

# define HERE_FILE ".herefile.tmp"
# define HERE2FILE ".herefile_.tmp"

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

typedef enum e_type		t_type;
typedef enum e_error	t_error;
typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

enum e_type
{
	ERROR = 0,
	WORD,
	NBR,
	PIPE,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	QUOTE,
	DQUOTE,
	VAR,
	VAR_QUOTE
};

enum e_error
{
	no_error = 0,
	error_operator,
	error_quote,
	error_redirection,
	error_pipe
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

/********************/

/*		PARSER		*/

typedef struct s_cmd	t_cmd;
typedef struct s_red	t_red;
typedef enum e_redt		t_redt;

enum	e_redt
{
	redir_nbr = 1,
	redir_append,
	redir_write,
	redir_read,
	redir_heredoc
};

/*
 *	the flag variable is for heredoc
 *	if set variable expansion is not activated.
 */

struct s_red
{
	t_redt	type;
	int		flag;
	int		fd_in;
	int		fd_out;
	char	*data;
	t_red	*next;
};

struct s_cmd
{
	char	*cmd_name;
	char	**cmd_args;
	int		buffer_size;
	t_red	*redirection;
	t_cmd	*next;
};

/********************/

/*		ENV VAR		*/

typedef struct s_env	t_env;

struct s_env
{
	char	*env_full;
	char	*env_key;
	char	*env_value;
	t_env	*next;
};

/********************/

/*		SHELL		*/

typedef struct s_shell	t_shell;

struct s_shell
{
	t_cmd	*first_cmd;
	t_env	*env;
	int		return_status;
};

/********************/

/*		ENV VAR		*/

void	parse_env(char **envp, t_shell *shell);
char	**env_to_str(t_shell *shell);
void	destroy_env(t_env *head);
char	*get_env_var(t_shell *shell, char *str);
void	var_expansion(t_shell *shell);

/********************/

void	parser(t_lexer *lexer, t_shell *shell);

int		quote(char *str, t_lexer *lexer);
int		dollar(char *str, t_lexer *lexer, t_type type);
int		operator(char *str, t_lexer *lexer);
int		word(char *str, t_lexer *lexer);

int		comment(char *str, t_lexer *lexer);
int		skip_space(char *str, t_lexer *lexer);
int		is_number(char *str, int len);
int		size_var(char *str, char tmp);
int		is_operator(char c);

void	handle_quote(t_shell *shell, t_lexer *lexer, \
		t_cmd *current, int *index);
int		check_var(char *str);
int		get_end(char *str);

void	handle_redirection(t_lexer *lexer, t_cmd *current, int *index);
void	handle_word(t_lexer *lexer, t_cmd *current, int *index);
void	handle_pipe(t_cmd **current, int *index);

void	destroy_cmd(t_cmd *cmd);
void	create_cmd(t_cmd **cmd);
int		get_nbr_cmds(t_lexer *lexer);
void	dump_cmds(t_cmd *cmd);

int		append_cmd_args(char *str, t_cmd *cmd);

void	create_token(char *str, int len, t_type type, t_lexer *lexer);
void	dump_tokens(t_lexer *lexer);

/*		UTILS		*/

char	*str_insert(char *str, int start_insert, int size_insert, char *insert);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_env **alst, t_env *new);

int		is_redirection(t_type type);

/*		EXECUTION		*/

void	executor(t_shell *shell);

#endif
