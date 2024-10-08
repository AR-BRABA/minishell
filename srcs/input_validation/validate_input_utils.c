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
 * Checks for unclosed quotes in user input
 *
 * @param input - user input
 * @return -1 - if there are unclosed quotes, otherwise returns the position of
 * the char after the quotes close
 */
/*int	check_unclosed_quotes(char *input)
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
}*/

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

/**
 * Checks if user input contains only spaces
 *
 * @param input - user input
 * @return true - if input contains only spaces, false otherwise
 */
bool	has_only_spaces(char *input)
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
/*
int	check_unclosed_quotes(char *input)
{
	char	*str;

	str = input;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (*str != '\'')
				return (-1);
			str++;
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
			{
				if (*str == '$')
				{
					// How to handle '$' within double quotes?
				}
				str++;
			}
			if (*str != '\"')
				return (-1);
			str++;
		}
		else
			str++;
	}
	return (str - input);
}*/
