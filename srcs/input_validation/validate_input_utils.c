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
 * Skips spaces in the given string and advances the pointer
 *
 * @param input - Pointer to the current position in the string
 */
void	skip_spaces(char **input)
{
    while (**input && ft_isspace(**input))
        (*input)++;
}

bool	check_unclosed_quotes(char *s)
{
	bool	unclosed_single_quotes;
	bool	unclosed_double_quotes;

	unclosed_single_quotes = false;
	unclosed_double_quotes = false;
	while (*s)
	{
		if (*s == '\"')
		{
			while (*s && *s != '\"')
				s++;
			if (*s == '\"')
				unclosed_double_quotes = !unclosed_double_quotes;
			check_unclosed_quotes(s + 1);
		}
		else if (*s == '\'')
		{
			while (*s && *s != '\'')
				s++;
			if (*s == '\'')
				unclosed_single_quotes = !unclosed_single_quotes;
			check_unclosed_quotes(s + 1);
		}
		s++;
	}
	return (unclosed_single_quotes || unclosed_double_quotes);
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