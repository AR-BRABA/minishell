/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2024/08/26 16:49:14 by jgils            ###   ########.fr       */
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
}	t_tab;

// DISPLAY_PROMPT.C -----------------------------------------------------------
char	*read_input(char *user_input);

// VALIDATE_INPUT.C -----------------------------------------------------------
bool	validate_input(char *input);


// TOKENIZER.C ----------------------------------------------------------------
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


// TOKENIZER_UTILS.C ----------------------------------------------------------
char	*strtrim_space(char *s1);

/*
* ft_substr but starting by the first index of str
*/
char	*substr_by_address(char *str, int len);

// PRINT.C --------------------------------------------------------------------
void	print_split(char **array);
void	print_list(t_list *list);
void	print_tab(t_tab	*table);

// FREE.C ---------------------------------------------------------------------
void	free_split(char **array);

// IDENTIFY_CHAR.C ------------------------------------------------------------
int	is_operator(char c);
int	is_quote(char c);
int	is_space(char c);
int	is_metachar(char c);

// COMMAND_TABLE.C ------------------------------------------------------------


#endif
