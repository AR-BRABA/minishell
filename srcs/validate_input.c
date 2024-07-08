/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/28 16:09:55 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Checks for unclosed quotes in user input
 *
 * @param input - user input
 * @return -1 - if there are unclosed quotes, otherwise returns the position of the char after the quotes close
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

/**
 * Checks if user input starts or ends with '|', '<' or '>'
 *
 * @param input - user input
 * @return false - if input starts or ends with '|', '<' or '>', true otherwise
 */
bool	check_special_chars(char *input)
{
	char	*special_chars;

	special_chars = "|<>";
	if (ft_strchr(special_chars, input[0])
		|| ft_strchr(special_chars, input[ft_strlen(input) - 1]))
		return (true);
	return (false);
}

/**
 * Validates user input by checking various conditions
 *
 * @param input (user input)
 * @return true (if user input is valid, false otherwise)
 */
bool	validate_input(char *input)
{
	if (check_unclosed_quotes(input) == -1)
	{
		fprintf(stderr, "Error: Unclosed quotes in input.\n");
		return (false);
	}
	if (check_special_chars(input))
	{
		fprintf(stderr, "Error: Special chars at the beginning or"
			"end of the input.\n");
		return (false);
	}
	return (true);
}
