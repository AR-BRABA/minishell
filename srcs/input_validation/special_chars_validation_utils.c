/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:59:21 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 16:52:00 by tsoares-         ###   ########.fr       */
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
	while (*input)
	{
		if ((*input == '>' || *input == '<'))
		{
			input++;
			skip_spaces(&input);
			if (*input == '|') // > ou < seguido de |
				return (false);
		}
		else
			input++;
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
	int		count;

	current_char = '\0';
	count = 0;
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			skip_spaces(&input);
			if (*input == '>' || *input == '<') // | seguido de > ou <
			{
				current_char = *input;
				count = 0;
				while (*input == current_char) // > ou < consecutivos depois de |
				{
					count++;
					input++;
				}
				if (count > 2) // + de dois > ou < consecutivos
					return (false);
			}
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
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			skip_spaces(&input);
			if (*input == '|')
				return (false);
		}
		else
			input++;
	}
	return (true);
}

/**
 * Validates that redirection operators ('<' or '>') are not used consecutively
 * more than twice and are not improperly spaced
 *
 * This function checks the user's input to ensure that:
 *   - no more than two consecutive redirection operators are used
 *   - redirection operators are not followed by another redirection operator 
 *     after spaces (e.g., '>> >' or '<< <' are invalid).
 *
 * @param input  - The user's input string to validate
 * @return true  - If no invalid redirection sequences are found
 * @return false - If more than two consecutive redirections or invalid 
 *                 spacing is detected
 */
bool	consecutive_redirects(char *input)
{
	char	current_char;
	int		count;

	current_char = '\0';
	count = 0;
	while (*input)
	{
		if (*input == '>' || *input == '<')
		{
			current_char = *input;
			count = 0;
			while (*input == current_char) // > ou < consecutivos
			{
				count++;
				input++;
			}
			if (count > 2) // + de 2 > ou < consecutivos
				return (false);
			skip_spaces(&input);
			if (*input == '>' || *input == '<')
				return (false);
		}
		else
			input++;
	}
	return (true);
}
