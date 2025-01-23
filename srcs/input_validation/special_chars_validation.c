/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/21 17:22:12 by tsoares-         ###   ########.fr       */
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
	char *end;

	end = input;
	if (!input || *input == '\0')
		return (false);

	while (*input && ft_isspace(*input))
		input++;

	if (*input == '|' || *input == '<' || *input == '>')
		return (true);

	// ir pro fim da str
	while (*end)
		end++;

	// pular espaços do final
	while (end > input && ft_isspace(*(end - 1)))
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
bool check_pipe_redirect_sequences(char *input)
{
    char    current;
    int     count;
    
    current = *input;
    count = 0;
    while (*input)
    {
        if (*input == '|' || *input == '<' || *input == '>')
        {
            count = 1; //pra contar o char atual
            input++;
            skip_spaces(&input);
            while (*input == current) // ver chars iguais em sequÊncia
            {
                count++;
                input++;
                skip_spaces(&input);
                if ((current == '>' || current == '<') && count > 2) // mais de 2 > ou <
                    return false;
                if (current == '|' && count > 1) // mais de um |
                    return false;
            }
            if ((current == '>' || current == '<') && *input == '|')
                return false;
            if (current == '|' && (*input == '>' || *input == '<'))
                return true;
        }
        else
            input++;
    }
    return true;
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
