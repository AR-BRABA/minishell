/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2024/07/10 21:57:42 by jgils            ###   ########.fr       */
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


// PARSER.C -------------------------------------------------------------------
/*
 * count the amount of tokens in an input
 */
int	count_tokens(char *input);

/*
* splits user_input into an array of tokens.
* lexical analisis divides tokens by: >, <, |, <<, >>, '...', "..." and SPACE
*/
char	**tokenizer(char *user_input);


// PARSER_UTILS.C -------------------------------------------------------------
char	*strtrim_space(char *s1);

#endif
