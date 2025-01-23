/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:06 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (check_unclosed_quotes(input)
		|| check_border_special_chars(input)
		|| !check_invalid_sequences(input)
		|| !check_pipe_redirect_sequences(input))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (false);
	}
	return (true);
}
