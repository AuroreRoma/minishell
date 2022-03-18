/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:11:30 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 17:48:58 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "../libft/libft.h"

# define TOK_BUFFER_SIZE 64
# define ARG_BUFFER_SIZE 32
# define RED_BUFFER_SIZE 16

# define SHELL_NAME "minishell"
# define HEREDOC_PROMPT "> "

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
	VAR_QUOTE,
	_SPACE
};

enum e_error
{
	no_error = 0,
	error_operator,
	error_quote,
	error_redirection,
	error_pipe,
	error_malloc
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
	t_env	*sorted_next;
};

/********************/

/*		SHELL		*/

typedef struct s_shell	t_shell;

struct s_shell
{
	t_cmd	*first_cmd;
	t_env	*env;
	t_env	*env_sorted;
	char	**env_str;
	int		return_status;
	int		nbr_cmd;
	int		stdio[2];
};

/********************/

/*		ENV VAR		*/

void	parse_env(char **envp, t_shell *shell);
void	sort_env(t_shell *shell);
void	add_env(char *var_line, t_shell *shell);
char	**env_to_str(t_shell *shell);
void	destroy_env(t_env *head);
void	destroy_env_str(char **env);
char	*get_env_var(t_shell *shell, char *str);
void	var_expansion(t_shell *shell);
void	var_expansion_heredoc(t_shell *shell, t_red *current);
void	var_expansion_redirection(t_shell *shell, t_red *current);
void	replace_var(t_shell *shell, char **ptr);
void	search_and_replace_var(t_shell *shell, char **line);
void	var_replace_line(t_shell *shell, char **line);
void	var_expansion_cmd_args(t_shell *shell, t_cmd *cmd, char **cmd_args);

/********************/

int		parser_lexer(t_shell *shell, char *str);

int		quote(char *str, t_lexer *lexer);
int		dollar(char *str, t_lexer *lexer, t_type type);
int		operator(char *str, t_lexer *lexer);
int		word(char *str, t_lexer *lexer);

int		comment(char *str, t_lexer *lexer);
int		skip_space(char *str, t_lexer *lexer);
int		is_number(char *str, int len);
int		size_var(char *str, char tmp);
int		is_operator(char c);

int		check_var(char *str);
int		get_end(char *str);

char	*generate_herefile_name(void);
void	handle_redirection(\
			t_shell *shell, t_lexer *lexer, t_cmd *current, int *index);
void	handle_word(t_lexer *lexer, t_cmd *current, char *str, int *index);
void	handle_space(t_lexer *lexer, t_cmd *current, int *index);
void	handle_pipe(t_cmd **current, int *index);
void	handle_heredoc(t_lexer *lexer, t_red *new, int *index, int *wstatus);

void	join_token(t_lexer *lexer, int *index);

void	destroy_cmd(t_cmd *cmd);
void	create_cmd(t_cmd **cmd);
int		get_nbr_cmds(t_lexer *lexer);
void	dump_cmds(t_cmd *cmd);

int		append_cmd_args(char *str, t_cmd *cmd);

void	create_token(char *str, int len, t_type type, t_lexer *lexer);
void	dump_tokens(t_lexer *lexer);
void	destroy_tokens(t_lexer *lexer, t_token *tokens);
void	tokenizer(t_lexer *lexer, char *str);

/*		UTILS		*/

char	*str_insert(char *str, int start_insert, int size_insert, char *insert);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_env **alst, t_env *new);
void	*ft_realloc(void *ptr, size_t old, size_t new, size_t size);

char	*remove_quote(char *string);
char	*remove_quote_2_le_retour(char *string);

int		is_redirection(t_type type);
int		is_arg(t_type type);

char	*generate_herefile_name(void);

int		export_check_args(t_shell *shell, char *str);
int		export_no_args(t_shell *shell);
char	*ft_join_env(char const *s1, char const *s2);

void	clean(t_shell *shell);

/*		SIGNALS			*/

void	signal_handler(int num);
void	signal_handler_heredoc(int num);
void	signal_handler_exec(int num);

/*		EXECUTION		*/

void	executor(t_shell *shell);
int		redirections(t_cmd *cmd);
void	cmd_launcher(t_shell *shell, t_cmd *cmd);
void	cmd_launcher_absolute(t_shell *shell, t_cmd *cmd);
void	cmd_launcher_relative(t_shell *shell, t_cmd *cmd);

void	destroy_child_pipeline(t_shell *shell, int **pipe_array, \
		int exit_status, int flag);
void	destroy_child_exec(t_shell *shell, int exit_status);
void	close_all_the_pipes(int n_pipes, int **pipes);

void	pipeline(t_shell *shell);

/*		BUILTINS		*/

void	set_builtins(t_cmd *cmd);
int		run_builtin(t_shell *shell, t_cmd *cmd);
int		ft_pwd(t_shell *shell);
int		ft_echo(t_shell *shell, t_cmd *cmd);
int		ft_cd(t_shell *shell, t_cmd *cmd);
int		ft_env(t_shell *shell, t_cmd *cmd);
int		ft_export(t_shell *shell, t_cmd *cmd);
int		ft_unset(t_shell *shell, t_cmd *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);

void	update_env(t_shell *shell, char *key, char *value);

#endif
