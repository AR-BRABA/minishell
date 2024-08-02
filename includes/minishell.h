/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2024/07/23 02:32:01 by jgils            ###   ########.fr       */
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

// DISPLAY_PROMPT.C -----------------------------------------------------------
char	*read_input(char *user_input);

// VALIDATE_INPUT.C -----------------------------------------------------------
bool	validate_input(char *input);


// TOKENIZER.C ----------------------------------------------------------------
/*
 * count the amount of tokens in an input
 */
int	count_tokens(char *input);

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

// FREE.C ---------------------------------------------------------------------
void	free_split(char **array);

// IDENTIFY_CHAR.C ------------------------------------------------------------
int	is_operator(char c);
int	is_quote(char c);
int	is_space(char c);
int	is_metachar(char c);

#endif
