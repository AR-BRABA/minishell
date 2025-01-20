/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:03:53 by tsoares-          #+#    #+#             */
/*   Updated: 2024/09/27 09:12:44 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Checks if all quotes in a string are properly closed
 *
 * This function goes trough the given string and verifies if all single and
 * double quotes have matching pairs. It returns true if all quotes are
 * properly closed. If any unclosed quote is found, it returns false ('\0').
 *
 * @param input - The user input string to be checked for unclosed quotes
 * @return true - If all quotes are closed properly
 * @return false ('\0) - If there is any unclosed quote in the input string
 */
bool	check_unclosed_quotes(char *input)
{
	char current_quote;
	
	current_quote = '\0';

    while (*input) {
        if ((*input == '\'' || *input == '"')) {
            if (current_quote == '\0') {
                current_quote = *input;
            } else if (*input == current_quote) {
                current_quote = '\0';
            }
        }
        input++;
    }
    return (current_quote == '\0');
}

/**
 * Checks if user input is an empty string or contains only spaces
 *
 * @param input - user input
 * @return true - if input is empty or contains only spaces, false otherwise
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

bool	dollar_within_quotes(char *input, int *pos, char quote_char)
{
	while (input[*pos] && input[*pos] == '$')
	{
		if (quote_char == '\"' && input[*pos] == '$')
		{
			// Handle the dollar sign within double quotes
		}
		else
		{
			check_unclosed_quotes(input);
			break;
		}
	}
	(*pos)++;
	if (input[*pos] != quote_char)
		return (false); // Unclosed quotes
	(*pos)++;
	return (true);
}
