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
 * Validates the input to ensure '<' or '>' is not followed by '|'
 * and '|' is not followed by '<' or '>', ignoring spaces in between.
 *
 * @param input - The user input string to validate
 * @return true - If no invalid sequences is found
 * @return false - If an invalid sequence is detected
 */
 bool check_invalid_sequences(char *input)
{
    while (*input)
    {
        if (*input == '<' || *input == '>')
        {
            input++;
            while (*input && ft_isspace(*input))
                input++;
            if (*input == '|')
                return false;
        }
        else if (*input == '|')
        {
            input++;
            while (*input && ft_isspace(*input))
                input++;
            if (*input == '<' || *input == '>')
                return false;
        }
        else
        {
            input++;
        }
    }
    return true;
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