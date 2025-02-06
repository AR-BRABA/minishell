/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:03:53 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 15:49:15 by tsoares-         ###   ########.fr       */
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
