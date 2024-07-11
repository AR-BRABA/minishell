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

/**
 * Checks for unclosed quotes in user input
 *
 * @param input - user input
 * @return -1 - if there are unclosed quotes, otherwise returns the position of
 * the char after the quotes close
 */
int	check_unclosed_quotes(char *input)
{
	bool	single_quote_open;
	bool	double_quote_open;
	int		pos;

	single_quote_open = false;
	double_quote_open = false;
	pos = 0;
	while (input[pos])
	{
		if (input[pos] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (input[pos] == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		pos++;
	}
	if (single_quote_open || double_quote_open)
		return (-1);
	return (pos);
}
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
		if (*input == '<')
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
	// >>>>>>>>>>> Give the prompt back to user
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
	{
		fprintf(stderr, "GIVE THE PROMPT BACK TO USER.\n");
		return (false);
	}
	if (check_unclosed_quotes(input) == -1)
	{
		fprintf(stderr, "Error: Unclosed quotes in input.\n");
		return (false);
	}
	if (check_border_special_chars(input))
	{
		fprintf(stderr, "Error: Special chars at the beginning or"
			" end of the input.\n");
		return (false);
	}
	return (true);
}
