/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/24 21:28:26 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Checks for unclosed quotes in user input
 *
 * @param input - user input
 * @return true - if there are unclosed quotes, false otherwise
 */

bool	check_unclosed_quotes(char *input)
{
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	while (*input)
	{
		if (*input == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (*input == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		input++;
	}
	return (single_quote_open || double_quote_open);
}

/**
 * Validates user input by checking various conditions
 *
 * @param input (user input)
 * @return true (if user input is valid, false otherwise)
 */
bool	validate_input(char *input)
{
	if (check_unclosed_quotes(input))
	{
		fprintf(stderr, "Error: Unclosed quotes in input.\n");
		return (false);
	}
	return (true);
}
