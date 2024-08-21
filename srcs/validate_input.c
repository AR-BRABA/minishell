/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2024/07/10 23:44:00 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
bool	check_redirection_syntax(char *input)
{
	char	*redirections;

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

/**
 * Checks if user input starts or ends with '|', '<' or '>'
 *
 * @param input - user input
 * @return true - if input starts or ends with '|', '<' or '>', false otherwise
 */
bool	check_border_special_chars(char *input)
{
	char	*special_chars;

	special_chars = "|<>";
	if (*input == '<' && *(input + 1) == '<')
	{
		input += 2;
		while (*input && ft_isspace(*input) && *input != '<')
			input++;
		if (*input == '<' || ft_isspace(*input) || !*input)
			return (true);
		return (false);
	}
	if (ft_strchr(special_chars, input[0])
		|| ft_strchr(special_chars, input[ft_strlen(input) - 1]))
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
	if (check_unclosed_quotes(input))
	{
		write(2, "Error: Unclosed quotes in input.\n", 33);
		return (false);
	}
	/*
	if (check_unclosed_quotes(input)
		|| check_border_special_chars(input))
	{
			write (2, "Error\n", 6);
			return (false);
	}*/
	if (check_border_special_chars(input))
	{
		write(2, "Error: Special chars at the beginning or end of the input.\n", 59);
		return (false);
	}
	return (true);
}
