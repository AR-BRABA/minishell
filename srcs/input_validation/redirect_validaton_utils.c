#include "../../includes/minishell.h"

bool	check_redirect_count(char **input, char current_char)
{
	int	count;

	count = 0;
	while (**input == current_char)
	{
		count++;
		(*input)++;
	}
	if (count > 2)
	{
		return (error("Syntax error: too many redirections after '|'\n",
				46, false));
	}
	return (true);
}

bool	check_consecutive_redirects(char **input, char current_char)
{
	int	count;

	count = 0;
	while (**input == current_char)
	{
		count++;
		(*input)++;
	}
	if (count > 2)
	{
		return (error("Syntax error: more than two consecutive redirections\n",
				53, false
			));
	}
	return (true);
}

bool	check_invalid_redirect_sequence(char **input)
{
	skip_spaces(input);
	if (**input == '>' || **input == '<')
	{
		return (error("Syntax error: invalid redirection sequence\n",
				43, false
			));
	}
	return (true);
}

/**
 * Validates that redirection operators ('<' or '>') are not used consecutively
 * more than twice and are not improperly spaced
 *
 * This function checks the user's input to ensure that:
 *   - no more than two consecutive redirection operators are used
 *   - redirection operators are not followed by another redirection operator 
 *     after spaces (e.g., '>> >' or '<< <' are invalid).
 *
 * @param input  - The user's input string to validate
 * @return true  - If no invalid redirection sequences are found
 * @return false - If more than two consecutive redirections or invalid 
 *                 spacing is detected
 */
bool	consecutive_redirects(char *input)
{
	char	current_char;

	current_char = '\0';
	while (*input)
	{
		if (*input == '>' || *input == '<')
		{
			current_char = *input;
			if (!check_consecutive_redirects(&input, current_char))
				return (false);
			if (!check_invalid_redirect_sequence(&input))
				return (false);
		}
		else
			input++;
	}
	return (true);
}
