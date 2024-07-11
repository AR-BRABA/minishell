/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:03:53 by tsoares-          #+#    #+#             */
/*   Updated: 2024/07/11 06:03:55 by tsoares-         ###   ########.fr       */
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