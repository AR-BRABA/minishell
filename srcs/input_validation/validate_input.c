/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:06 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
bool	check_redirection_syntax(char *input)
{
	char	*redirections;
	char	*special_chars;

	redirections = "<>";
	// check_uclosed_quotes
	while (*input)
	{
		if (ft_strchr(redirections, *input))
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			// check_unclosed_quotes
		}
	}
}*/

/*
 * Validates if the input starts or ends with special characters:
 * '|', '<', '>', '<<' or '>>'
 *
 * This function checks the user's input to ensure it doesn't start or
 * end with special characters that would make the command invalid.
 *
 * @param input - The user input string to validate
 * @return true - If input doesn't start/end with special characters
 * @return false - If input starts/ends with '|', '<', '>', '<<' or '>>'
 */
 bool	check_border_special_chars(char *input)
{
	char *end;

	end = input;
	if (!input || *input == '\0')
		return (false);

	while (*input && ft_isspace(*input))
		input++;

	if (*input == '|' || *input == '<' || *input == '>')
		return (true);

	// ir pro fim da str
	while (*end)
		end++;

	// pular espaços do final
	while (end > input && ft_isspace(*(end - 1)))
		end--;

	if (*(end - 1) == '|' || *(end - 1) == '<' || *(end - 1) == '>')
		return (true);

	return (false);
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

/**
 * Validates user input by checking various conditions
 *
 * @param input (user input)
 * @return true (if user input is valid, false otherwise)
 */
bool	validate_input(char *input)
{
	if (check_empty_input(input))
		return (false);
	if (check_unclosed_quotes(input)
		|| check_border_special_chars(input)
		|| !check_invalid_sequences(input))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (false);
	}
	return (true);
}
