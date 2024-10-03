/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/03 14:29:01 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

enum e_type {
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_FILE,
	APPEND,
	HEREDOC,
};

enum e_std {
	STD_IN,
	STD_OUT,
	STD_ERROR,
};

typedef struct	s_node {
	char	*value;
	int	type;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct	s_list {
	int	len;
	t_node	*head;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct	s_tab {
	t_list	*head;
	int	len;
	int	fd_in;
	int	fd_out;
}	t_tab;

typedef struct	s_envnode {
	char	*key;
	char	*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
} t_envnode;

typedef struct	s_env {
	int	len;
	t_envnode	*head;
	t_envnode	*tail;
} t_env;

// DISPLAY_PROMPT.C -----------------------------------------------------------
char	*read_input(char *user_input);

// VALIDATE_INPUT.C -----------------------------------------------------------
bool	validate_input(char *input);
bool    check_unclosed_quotes(char *s);
bool    has_only_spaces(char *input);

// ENV.C -----------------------------------------------------------------------
t_envnode	*new_envnode(char *envp);
void	addback_env(t_envnode *newnode, t_env *list);
t_env	*get_env_list(char **envp);
void	print_env(t_env	*env);

// PRINT.C --------------------------------------------------------------------
void	print_split(char **array);
void	print_list(t_list *list);
void	print_tab(t_tab	*table);

// FREE.C ---------------------------------------------------------------------
void	free_split(char **array);
void	destroy_table(t_tab *cmdtable);

// IDENTIFY_CHAR.C ------------------------------------------------------------
int	is_operator(char c);
int	is_quote(char c);
int	is_space(char c);
int	is_metachar(char c);

// LEXER.C --------------------------------------------------------------------
/*
 * count the amount of tokens in an input
 */
int	count_tokens(char *input);
char	**metachar_split(char *user_input);

/*
* splits user_input into an array of tokens.
* lexical analisis divides tokens by: >, <, |, <<, >>, '...', "..." and SPACE
*/
char	**get_tokens(char *user_input);


// LEXER_UTILS.C --------------------------------------------------------------
char	*strtrim_space(char *s1);
char	*substr_by_address(char *str, int len);

/*
* ft_substr but starting by the first index of str
*/
char	*substr_by_address(char *str, int len);

// TOKENIZER.C ----------------------------------------------------------------
t_tab	*get_cmdtable(char **input, t_env *env);
void	identify_tokens(t_tab *cmdtable);
void	get_type(t_node *token);
void	get_redirect_type(t_node *token);

// TOKENIZER_UTILS.C ----------------------------------------------------------
int	cmdlen(char **input);
void	add_node(t_node *newnode, t_list *list);
void	add_list(t_list *newnode, t_tab *cmdtable);
t_node	*new_node(char *token);
t_list	*new_list(char **input);

// TOKEN_FORMAT.C ------------------------------------------------------------
void	rm_quote(t_node *token);
void	format(t_tab *cmdtable, t_env *env);
t_envnode	*search_key(t_env *list, char *key);

#endif
