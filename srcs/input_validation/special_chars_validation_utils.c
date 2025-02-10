/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:59:21 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 23:04:45 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Validates that '<' or '>' is not followed by '|'
 *
 * This function checks the user's input to ensure that redirection 
 * operators ('<' or '>') are not directly followed by a pipe ('|'), 
 * ignoring any spaces between them
 *
 * @param input  - The user's input string to validate
 * @return true  - If '<' or '>' is not followed by '|'
 * @return false - If '<' or '>' is immediately followed by '|'
 */
bool	redirects_followed_by_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_str(input, i) && (input[i] == '>' || input[i] == '<'))
		{
			i++;
			skip_spaces(&input);
			if (input[i] == '|')
				return (error_return(
						"Syntax error: '|' after redirection\n", 36, false
					));
		}
		else
			i++;
	}
	return (true);
}

/**
 * Validates that '|' is not followed by invalid redirection sequences
 *
 * This function ensures that when a pipe is followed by a redirection 
 * operator, the sequence is valid.
 *
 * Specifically, it checks:
 *    - a '|' can be followed by at most two consecutive redirection operators
 *      (e.g., '|>>' or '|<<' are valid, but '|>>>' or '|<<<' are invalid)
 *
 * @param input  - The user's input string to validate
 * @return true  - If all sequences following '|' are valid
 * @return false - If any invalid sequence is detected after '|'
 */
bool	pipe_followed_by_redirects(char *input)
{
	char	current_char;

	current_char = '\0';
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			skip_spaces(&input);
			if (!check_redirect_count(&input, current_char))
				return (false);
		}
		else
			input++;
	}
	return (true);
}

/**
 * Validates that there are no consecutive pipes in the input
 *
 * This function checks the user's input to ensure that two pipe ('|') 
 * operators are not used consecutively, even if separated by spaces.
 *
 * @param input  - The user's input string to validate
 * @return true  - If there are no consecutive pipes in the input
 * @return false - If two consecutive pipes or more are detected
 */
bool	consecutive_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_str(input, i) && input[i] == '|')
		{
			i++;
			while (input[i])
			{
				if (ft_isspace(input[i]))
					i++;
				else if (input[i] && input[i] == '|')
					return (error_return("Syntax error: consecutive pipes\n",
							32, false));
				else
					break ;
			}
		}
		else
			i++;
	}
	return (true);
}
