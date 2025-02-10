/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 21:56:15 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	IN_FILE,
	OUT_FILE,
	HEREDOC_DELIMITER,
	APPEND,
	HEREDOC,
};

typedef struct s_node
{
	char				*value;
	int					type;
	struct s_node		*prev;
	struct s_node		*next;
}						t_node;

typedef struct s_list
{
	int					len;
	t_node				*head;
	int					fd[2];
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

typedef struct s_tab
{
	t_list				*head;
	int					len;
}						t_tab;

typedef struct s_envnode
{
	char				*key;
	char				*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
}						t_envnode;

typedef struct s_env
{
	int					len;
	t_envnode			*head;
	t_envnode			*tail;
}						t_env;

typedef struct s_main
{
	t_env				*envp_list;
	char				**envp;
	t_tab				*cmdtab;
	int					fd[2];
}						t_main;

extern int				g_tecno_status;

// DISPLAY_PROMPT.C ------------------------------------------------------------
char					*read_input(char *user_input);

// VALIDATE_INPUT.C ------------------------------------------------------------
bool					check_border_special_chars(char *input);
bool					check_consecutive_redirects(char *input, int i);
bool					check_empty_input(char *input);
bool					check_invalid_sequences(char *input);
bool					check_pipe_redirect_sequences(char *input);
bool					check_redirect_count(char **input,
							char current_char);
bool					check_unclosed_quotes(char *s);
bool					consecutive_pipes(char *input);
bool					consecutive_redirects(char *input);
bool					error_return(char *error_msg, int n_chars,
							bool return_value);
bool					exceed_redir_msg(void);
bool					is_str(char *input, int pos);
bool					pipe_followed_by_redirects(char *input);
bool					redirects_followed_by_pipe(char *input);

void					skip_spaces(char **input);
bool					validate_input(char *input);

// ENV.C -----------------------------------------------------------------------
t_envnode				*new_envnode(char *envp);
void					addback_env(t_envnode *newnode, t_env *list);
t_env					*get_env_list(char **envp);
int						ft_env(t_env *env);
int						ft_export(char **args, t_main *main);
int						ft_unset(char **args, t_main *main);
int						free_env(t_env *env);
int						ft_exit(char **args, t_main *main);
int						ft_exit_nbr(int nbr, t_main *main);
int						str_isname(char *str);
void					update_env(char *key, char *value, t_env *envp);
void					update_envnode(char *value, t_envnode *node);

// EXECUTOR.C ------------------------------------------------------------------
int						execute_builtins(t_list *cmdlist, t_main *main);
void					execute_commands(t_main *main);
void					execute_external_command(t_list *cmdlist, t_main *main);
int						execute_fork_commands(t_main *main);
char					*find_command_path(char *cmd, char **envp);
t_node					*get_cmd(t_list *cmdlist);
int						pre_exec(t_list *list);

// FD_MANAGEMENT.C -------------------------------------------------------------
void					manipulate_fd(t_list *cmdlist, int *fd, int *savefd,
							int *pid);
void					parent(t_list *cmdlist, int *fd, int *savefd);

// PROCESS_CONTROL.C -----------------------------------------------------------
int						freeturn(void *obj, int ret, int *fd, int *cmdfd);
int						pc_get_exit_status(t_main *main, int *pid);
int						*init_execute_fork_commands(int *savefd, int *n,
							t_main *main);

// PRINT.C ---------------------------------------------------------------------
void					print_split(char **array);
void					print_list(t_list *list);
void					print_tab(t_tab *table);

// FREE.C ----------------------------------------------------------------------
int						free_env(t_env *env);
void					free_list(t_list *cmdline);
void					free_envnode(t_envnode *node);

// FREE_UTILS.C ----------------------------------------------------------------
void					free_main(t_main *main);
void					free_table(t_tab *cmdtable);
void					free_split(char **array);

// IDENTIFY_CHAR.C -------------------------------------------------------------
int						is_operator(char c);
int						is_quote(char c);
int						is_space(char c);
int						is_metachar(char c);
int						is_name(char c);

// LEXER.C ---------------------------------------------------------------------
/*
 * count the amount of tokens in an input
 */
int						count_tokens(char *input);
char					**metachar_split(char *user_input);

// TOKEN_SPLIT_UTILS.C ---------------------------------------------------------
int						handle_non_metachar(char *input, int count);
int						handle_non_space_split(char *input, int count);
int						handle_operator(char *input, int count);
int						skip_spacesc(char *input, int count);

/*
 * splits user_input into an array of tokens.
 * lexical analisis divides tokens by: >, <, |, <<, >>, '...', "..." and SPACE
 * getcwd(buf, 0);
 */
char					**get_tokens(char *user_input);

// LEXER_UTILS.C ---------------------------------------------------------------
char					*strtrim_space(char *s1);
char					*substr_by_address(char *str, int len);

// UTILS.C ---------------------------------------------------------------------
int						ft_error(char *cmd, char *arg, char *message, int ret);
int						str_isname(char *str);
int						split_len(char **split);

/*
 * ft_substr but starting by the first index of str
 */
char					*substr_by_address(char *str, int len);

// TOKENIZER.C -----------------------------------------------------------------
t_tab					*get_cmdtable(char **input, t_env *env);
void					identify_tokens(t_tab *cmdtable);
void					get_type(t_node *token);
void					get_redirect_type(t_node *token);

// TOKENIZER_UTILS.C -----------------------------------------------------------
int						cmdlen(char **input);
t_list					*init_cmdlist(char **input);
void					find_command(t_node *token);

// TOKENIZER_UTILS.C -----------------------------------------------------------
void					add_node(t_node *newnode, t_list *list);
void					add_list(t_list *newnode, t_tab *cmdtable);
t_node					*new_node(char *token);
t_list					*new_list(char **input);

// FORMAT.C --------------------------------------------------------------------
void					format(t_tab *cmdtable, t_env *env);
int						strlen_isname(char *str);
char					*ft_strfjoin(char *s1, char *s2);
char					*ft_strnjoin(char *s1, char *s2, int n);

// ENV_SEARCH.C ----------------------------------------------------------------
char					*get_variable_value(t_env *env, char *var, int varlen);
t_envnode				*search_key(t_env *list, char *key);

// EXPANSION_UTILS.C -----------------------------------------------------------
int						decide_expansion(char *str, int dol, char *tmp);
void					expand(t_node *token, t_env *env);
char					*expand_variable(char *expanded, char *str, t_env *env);
int						strdol(char *str);

// QUOTE_UTILS.C ---------------------------------------------------------------
void					build_unquoted(char *quoted, char *unquoted);
void					rm_quote(t_node *token);
int						strlen_unquote(char *quotestr);

// ft_echo.C
// -----------------------------------------------------------------------------
int						ft_echo(char **arg);

// ft_cd.C
// -----------------------------------------------------------------------------
char					*get_key_value(t_env *list, char *key);
void					update_key_value(t_env *list, char *key, char *new_val);
int						ft_cd(char **args, t_main *main);
int						ft_error(char *cmd, char *arg, char *message, int ret);
int						split_len(char **split);

// ft_pwd.C
// -----------------------------------------------------------------------------
int						ft_pwd(void);

// redirect.c
int						redirect(t_list *cmdlist);

// convertions.c
char					**env_to_char_array(t_env *envp);
char					**list_to_char_array(t_node *token);
int						ft_exit_nbr(int nbr, t_main *main);

#endif
