/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:03:53 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 23:05:44 by tsoares-         ###   ########.fr       */
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

bool	check_double_quotes(char **s)
{
	while (**s && **s != '\"')
		(*s)++;
	if (**s == '\"')
	{
		(*s)++;
		return (false);
	}
	return (true);
}

bool	check_single_quotes(char **s)
{
	while (**s && **s != '\'')
		(*s)++;
	if (**s == '\'')
	{
		(*s)++;
		return (false);
	}
	return (true);
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
			s++;
			unclosed_double_quotes = check_double_quotes(&s);
		}
		else if (*s == '\'')
		{
			s++;
			unclosed_single_quotes = check_single_quotes(&s);
		}
		else
			s++;
	}
	if (unclosed_single_quotes || unclosed_double_quotes)
		write(STDERR_FILENO, "Syntax error: unclosed quotes\n", 30);
	return (unclosed_single_quotes || unclosed_double_quotes);
}

bool	is_str(char *input, int pos)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (i < pos && input[i])
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (in_single_quotes || in_double_quotes);
}
