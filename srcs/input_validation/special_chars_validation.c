/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 16:35:14 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Validates if the input starts or ends with the special characters:
 * '|', '<', '>', '<<' or '>>'
 *
 * This function ensures that the user's input does not start or end with
 * any of the special characters listed above
 *
 * @param input  - The user's input string to validate
 * @return true  - If input starts or ends with any of the special characters
 * @return false - If input does not start or end with any of the special
 * 		   characters
 */
bool	check_border_special_chars(char *input)
{
	char	*end;

	end = input;
	if (!input || *input == '\0')
		return (false);
	while (*input && ft_isspace(*input))
		input++;
	if (*input == '|')
	{
		error("Syntax error: unexpected '|'\n", 28);
		return (true);
	}
	while (*end)
		end++;
	while (end > input && ft_isspace(*(end - 1)))
		end--;
	if (*(end - 1) == '|' || *(end - 1) == '<' || *(end - 1) == '>')
	{
		error("Syntax error: input start/end with '|', '<' or '>'\n", 51);
		return (true);
	}
	return (false);
}

/**
 * Validates the input to ensure '<' or '>' is not followed by '|'
 * and '|' is not followed by '<' or '>', ignoring spaces in between.
 *
 * @param input  - The user input string to validate
 * @return true  - If no invalid sequences is found
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
			{
				error("Syntax error: unexpected '|'\n", 29);
				return (false);
			}
		}
		else if (*input == '|')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '<' || *input == '>')
			{
				error("Syntax error: '<' or '>' after '|'\n", 36);
				return (false);
			}
		}
		else
			input++;
	}
	return (true);
}

/**
 * Validates sequences involving the '|' operator combined with '<' or '>'
 *
 * Valdation rules:
 *    - valid cases: '<<', '>>', '|>', '|   >', '|<', '|   <', '|<<',
 *                   '|   <<', '|>>', '|   >>'
 *    - invalid cases:  '<   <', '>   >', '|<  <', '|   <   <', '|>  >',
 *			'|   >  >', '|>>>', '|    >>>', '|> >>',
 *			'|> > >', '| > >>', '| > > >', '|<<<', '|   <<<',
 *			'|< <<', '|< < <', '|<< <', '| < <<', '| << <',
 *			'| < < <', '>|', '> |', '<|', '<   |', '>>|',
 *			'> >|', '>>   |', '> > |', '<<|', '< <|', '<<   |',
 *			'< < |', '||', '|   |', '|||', '| ||', '|| |', '| | |' 
 *
 * @param input  - The user input string to validate
 * @return true  - If the sequence is valid
 * @return false - If the sequence is invalid
 */
bool	check_pipe_redirect_sequences(char *input)
{
	if (!redirects_followed_by_pipe(input))
		return (false);
	if (!consecutive_pipes(input))
		return (false);
	if (!pipe_followed_by_redirects(input))
		return (false);
	if (!consecutive_redirects(input))
		return (false);
	return (true);
}
