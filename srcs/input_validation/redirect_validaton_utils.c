/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_validaton_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:34:32 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 23:06:26 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_redirect_count(char **input, char current_char)
{
	int	count;

	count = 0;
	while (**input == current_char)
	{
		count++;
		(*input)++;
	}
	if (count > 2)
	{
		return (error_return("Syntax error: too many redirections after '|'\n",
				46, false));
	}
	return (true);
}

bool	check_consecutive_redirects(char **input, char current_char)
{
	int	count;

	count = 0;
	while (**input == current_char)
	{
		count++;
		(*input)++;
	}
	if (count > 2)
	{
		return (error_return(
				"Syntax error: more than two consecutive redirections\n",
				53, false
			));
	}
	return (true);
}

bool	check_invalid_redirect_sequence(char **input)
{
	skip_spaces(input);
	if (**input == '>' || **input == '<')
	{
		return (error_return("Syntax error: invalid redirection sequence\n",
				43, false
			));
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
	int		i;

	current_char = '\0';
	i = 0;
	while (input[i])
	{
		if (!is_str(input, i) && (input[i] == '>' || input[i] == '<'))
		{
			current_char = input[i];
			if (!check_consecutive_redirects(&input, current_char))
				return (false);
			if (!check_invalid_redirect_sequence(&input))
				return (false);
		}
		i++;
	}
	return (true);
}
