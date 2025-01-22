#include "../../includes/minishell.h"

int	get_count(char *input, int count)
{
	int	start;
	int	quote;

	quote = 0;
	start = count;
	if (is_operator(input[start]))
	{
		count++;
		if (is_operator(input[count]) && input[count] == input[start])
			count++;
	}
	else if (!is_metachar(input[start]))
	{
		while (input[count] != '\0' && !is_metachar(input[count]))
		{
			if (is_quote(input[count]))
			{
				quote = count++;
				while (input[count] != input[quote])
					count++;
			}
			count++;
		}
	}
	return (count);
}

int	count_tokens(char *user_input)
{
	int		count;
	int		tokens;
	char	*input;

	count = 0;
	tokens = 0;
	input = strtrim_space(user_input);
	while (input && input[count] != '\0')
	{
		count = get_count(input, count);
		tokens++;
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	free(input);
	return (tokens);
}

int	is_operator_end(char *input, int start)
{
	int	count;

	count = start;
	count++;
	if (is_operator(input[count]) && input[count] == input[start])
		count++;
	return (count);
}

int	is_not_space_end(char *input, int start)
{
	int	count;

	count = start;
	while (input[count] != '\0' && !is_metachar(input[count])
		&& !is_quote(input[count]))
		count++;
	return (count);
}

int	get_split_count(char *input, int count)
{
	int	start;
	int	quote;

	quote = 0;
	start = count;
	if (is_operator(input[start]))
		count = is_operator_end(input, start);
	else if (!is_metachar(input[start]))
	{
		while (input[count] != '\0' && !is_metachar(input[count]))
		{
			if (is_quote(input[count]))
			{
				quote = count++;
				while (input[count] != input[quote])
					count++;
			}
			count++;
		}
	}
	else if (!is_space(input[start]))
		count = is_not_space_end(input, start);
	return (count);
}

char	**metachar_split(char *user_input)
{
	int		count;
	int		start;
	int		token;
	char	**array;
	char	*input;

	count = 0;
	token = 0;
	input = strtrim_space(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (input && input[count] != '\0')
	{
		start = count;
		count = get_split_count(input, start);
		array[token++] = substr_by_address(&input[start], (count - start));
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	array[token] = NULL;
	free(input);
	return (array);
}
