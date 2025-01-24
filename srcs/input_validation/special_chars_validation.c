/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 15:47:48 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Validates if the input starts or ends with special characters:
 * '|', '<', '>', '<<' or '>>'
 *
 * This function checks the user's input to ensure it doesn't start or
 * end with special characters that would make the command invalid.
 *
 * @param input - The user input string to validate
 * @return true - If input doesn't start/end with special characters
 * @return false - If input starts/ends with '|', '<', '>', '<<' or '>>'
 */
bool	check_border_special_chars(char *input)
{
	char	*end;

	end = input;
	if (!input || *input == '\0')
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (*input == '|' || *input == '<' || *input == '>')
		return (true);
	while (*end) // ir pro fim da str
		end++;
	while (end > input && ft_isspace(*(end - 1))) // pular espaços do final
		end--;
	if (*(end - 1) == '|' || *(end - 1) == '<' || *(end - 1) == '>')
		return (true);
	return (false);
}

/**
 * Validates the input to ensure '<' or '>' is not followed by '|'
 * and '|' is not followed by '<' or '>', ignoring spaces in between.
 *
 * @param input - The user input string to validate
 * @return true - If no invalid sequences is found
 * @return false - If an invalid sequence is detected
 */
bool	check_invalid_sequences(char *input)
{
	while (*input)
	{
		if (*input == '<' || *input == '>')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '|')
				return (false);
		}
		else if (*input == '|')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '<' || *input == '>')
				return (false);
		}
		else
			input++;
	}
	return (true);
}

/**
 * Validates sequences with '|' combined with '<' or '>'
 *
 * This function ensures that:
 * - '|>' is valid.
 * - '|<' is valid.
 * - '>|' is invalid.
 * - '<|' is invalid.
 * Spaces between characters are skipped during validation.
 *
 * @param input - The user input string to validate
 * @return true - If the sequence is valid
 * @return false - If the sequence is invalid
 */
bool	check_pipe_redirect_sequences(char *input)
{
	//printf("\n\n\nDEBUG: Iniciando validação para input: '%s'\n", input); // DEBUG
	if (!redirects_followed_by_pipe(input))
	{
		//printf("DEBUG: redirects_followed_by_pipe falhou!\n"); // DEBUG
		return (false);
	}
	//printf("DEBUG: redirects_followed_by_pipe passou!\n"); // DEBUG
	if (!consecutive_pipes(input))
	{
		//printf("DEBUG: consecutive_pipes falhou!\n"); // DEBUG
		return (false);
	}
	//printf("DEBUG: consecutive_pipes passou!\n"); // DEBUG
	if (!pipe_followed_by_redirects(input))
	{
		//printf("DEBUG: pipe_followed_by_redirects falhou!\n"); // DEBUG
		return (false);
	}
	//printf("DEBUG: pipe_followed_by_redirects passou!\n"); // DEBUG
	if (!consecutive_redirects(input))
	{
		//printf("DEBUG: consecutive_redirects falhou!\n"); // DEBUG
		return (false);
	}
	//printf("DEBUG: consecutive_redirects passou!\n"); // DEBUG
	return (true);
}

/*
bool	check_redirection_syntax(char *input)
{
	char	*redirections;
	char	*special_chars;

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
