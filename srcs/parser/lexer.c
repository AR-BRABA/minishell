#include "../../includes/minishell.h"

int	handle_operator(char *input, int count)
{
	if (is_operator(input[count]))
	{
		count++;
		if (is_operator(input[count]) && input[count] == input[count - 1])
			count++;
	}
	return (count);
}

int	handle_non_metachar(char *input, int count)
{
	int	quote;

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
	return (count);
}

int	skip_spacesc(char *input, int count)
{
	while (is_space(input[count]))
		count++;
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
		count = handle_operator(input, count);
		if (!is_metachar(input[count]))
			count = handle_non_metachar(input, count);
		tokens++;
		count = skip_spacesc(input, count);
	}
	free(input);
	return (tokens);
}

// int	count_tokens(char *user_input)
// {
// 	int	count;
// 	int	start;
// 	int	quote;
// 	int	tokens;
// 	char	*input;
//
// 	count = 0;
// 	tokens = 0;
// 	input = strtrim_space(user_input);
// 	while (input && input[count] != '\0')
// 	{
// 		start = count;
// 		if (is_operator(input[start]))
// 		{
// 			count++;
// 			if (is_operator(input[count]) && input[count] == input[start])
// 				count++;
// 		}
// 		else if (!is_metachar(input[start]))
// 		{
// 			while (input[count] != '\0' && !is_metachar(input[count]))
// 			{
// 				if (is_quote(input[count]))
// 				{
// 					quote = count++;
// 					while (input[count] != input[quote])
// 						count++;
// 				}
// 				count++;
// 			}
// 		}
// 		tokens++;
// 		if (is_space(input[count]))
// 			while (is_space(input[count]))
// 				count++;
// 	}
// 	free(input);
// 	return (tokens);
// }

// char	**metachar_split(char *user_input)
// {
// 	int	count = 0;
// 	int	start = -1;
// 	int	token = 0;
// 	int	quote;
// 	char	**array;
// 	char	*input;
//
// 	input = strtrim_space(user_input);
// 	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
// 	while (input && input[count] != '\0')
// 	{
// 		start = count;
// 		if (is_operator(input[start]))
// 		{
// 			count++;
// 			if (is_operator(input[count]) && input[count] == input[start])
// 				count++;
// 		}
// 		else if (!is_metachar(input[start]))
// 		{
// 			while (input[count] != '\0' && !is_metachar(input[count]))
// 			{
// 				if (is_quote(input[count]))
// 				{
// 					quote = count++;
// 					while (input[count] != input[quote])
// 						count++;
// 				}
// 				count++;
// 			}
// 		}
// 		else if (!is_space(input[start]))
// 		{
// 			while (input[count] != '\0' && !is_metachar(input[count])
//				&& !is_quote(input[count]))
// 				count++;
// 		}
// 		array[token++] = substr_by_address(&input[start], (count - start));
// 		if (is_space(input[count]))
// 			while (is_space(input[count]))
// 				count++;
// 	}
// 	array[token] = NULL;
// 	free(input);
// 	return (array);
// }

int	handle_non_space_split(char *input, int count)
{
	while (input[count] != '\0' && !is_metachar(input[count])
		&& !is_quote(input[count]))
		count++;
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
	while (input && input[count] != '\0')
	{
		start = count;
		count = handle_operator(input, count);
		if (!is_metachar(input[start]))
			count = handle_non_metachar(input, count);
		else if (!is_space(input[start]))
			count = handle_non_space_split(input, count);
		array[token++] = substr_by_address(&input[start], (count - start));
		count = skip_spacesc(input, count);
	}
	array[token] = NULL;
	free(input);
	return (array);
}
