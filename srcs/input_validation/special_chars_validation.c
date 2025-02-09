/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 23:03:42 by tsoares-         ###   ########.fr       */
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
		return (error_return("Syntax error: unexpected '|'\n", 29, true));
	while (*end)
		end++;
	while (end > input && ft_isspace(*(end - 1)))
		end--;
	if (*(end - 1) == '|' || *(end - 1) == '<' || *(end - 1) == '>')
		return (
			error_return("Syntax error: input start/end with '|', '<' or '>'\n",
				51, true
			));
	return (false);
}

bool	is_invalid_redirection(char **input)
{
	(*input)++;
	while (**input && ft_isspace(**input))
		(*input)++;
	return (**input == '|');
}

bool	is_invalid_pipe(char **input)
{
	(*input)++;
	while (**input && ft_isspace(**input))
		(*input)++;
	return (**input == '<' || **input == '>');
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
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_str(input, i))
		{
			if ((input[i] == '>' || input[i] == '<')
				&& is_invalid_redirection(&input))
				return (error_return(
						"Syntax error: unexpected '|'\n", 29, false
					));
			if (input[i] == '|' && is_invalid_pipe(&input))
				return (error_return(
						"Syntax error: '<' or '>' after '|'\n", 36, false
					));
		}
		i++;
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
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_str(input, i))
		{
			if (!redirects_followed_by_pipe(&input[i])
				|| !consecutive_pipes(&input[i])
				|| !pipe_followed_by_redirects(&input[i])
				|| !consecutive_redirects(&input[i]))
				return (false);
		}
		i++;
	}
	return (true);
}
