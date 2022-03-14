/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wind <wind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:11:30 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/14 17:55:41 by wind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <errno.h>
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

# define HERE_FILE ".herefile_"
# define HERE2FILE ".herefile_.tmp"

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

typedef enum e_type		t_type;
typedef enum e_error	t_error;
typedef enum e_builtin	t_builtin;
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

enum e_builtin
{
	not_builtin = 0,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit
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
	redir_append = 1,
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
	int		redirect[2];
	int		builtin;
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
	char	**env_str;
	int		return_status;
	int		nbr_cmd;
	int		stdio[2];
};

/********************/

/*		ENV VAR		*/

void	parse_env(char **envp, t_shell *shell);
char	**env_to_str(t_shell *shell);
void	destroy_env(t_env *head);
void	destroy_env_str(char **env);
char	*get_env_var(t_shell *shell, char *str);
void	var_expansion(t_shell *shell);

/********************/

int		parser(t_shell *shell, char *str);

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

char	*generate_herefile_name(void);
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
void	destroy_tokens(t_lexer *lexer, t_token *tokens);
void	*tokenizer(t_lexer *lexer, char *str);

/*		UTILS		*/

char	*str_insert(char *str, int start_insert, int size_insert, char *insert);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_env **alst, t_env *new);

int		is_redirection(t_type type);

/*		SIGNALS			*/

void	signal_handler(int num);

/*		EXECUTION		*/

void	executor(t_shell *shell);
void	redirections(t_cmd *cmd);
void	cmd_launcher(t_shell *shell, t_cmd *cmd);
void	cmd_launcher_absolute(t_shell *shell, t_cmd *cmd);
void	cmd_launcher_relative(t_shell *shell, t_cmd *cmd);

void	pipeline(t_shell *shell);

/*		BUILTINS		*/

void	set_builtins(t_cmd *cmd);
int		run_builtin(t_shell *shell, t_cmd *cmd);
int		ft_pwd(t_shell *shell);
int		ft_echo(t_shell *shell, t_cmd *cmd);
int		ft_cd(t_shell *shell, t_cmd *cmd);
int		ft_env(t_shell *shell, t_cmd *cmd);
int		ft_unset(t_shell *shell, t_cmd *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);

#endif
