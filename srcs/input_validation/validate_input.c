/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 16:26:58 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Checks if user input is empty or contains only whitespace
 *
 * @param input  - The user's input string to check
 * @return true  - If the input is empty or contains only whitespaces
 * @return false - If the input contains any non-whitespace characters
 */
bool	check_empty_input(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (false);
		input++;
	}
	return (true);
}

void	error(char *error_msg, int n_chars)
{
	write(STDERR_FILENO, error_msg, n_chars);
}

/**
 * Validates the user's input by checking for syntax issues
 *
 * This function performs a series of checks to ensure the user's input is 
 * valid before further processing. It verifies:
 *   - the input is not empty or composed only of whitespace
 *   - there are no unclosed quotes in the input
 *   - the input does not start or end with invalid special characters
 *   - there are no invalid operator sequences (e.g., '<<<', '>>>', '||')
 *   - pipe and redirection sequences are used correctly
 *
 * @param input  - The user's input string to validate
 * @return true  - If the input passes all validation checks
 * @return false - If the input fails any of the validation checks
 */
bool	validate_input(char *input)
{
	if (check_empty_input(input))
		return (false);
	if (check_unclosed_quotes(input)
		|| check_border_special_chars(input)
		|| !check_invalid_sequences(input)
		|| !check_pipe_redirect_sequences(input))
	{
		g_tecno_status = 2;
		return (false);
	}
	return (true);
}
