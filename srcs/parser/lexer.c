#include "../../includes/minishell.h"

int	count_tokens(char *user_input)
{
	int	count = 0;
	int	start;
	int	quote;
	int	tokens = 0;
	char	*input;
	
	input = strtrim_space(user_input);
	while (input && input[count] != '\0')
	{
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
		tokens++;
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	return (tokens);
}

char	**metachar_split(char *user_input)
{
	int	count = 0;
	int	start = -1;
	int	token = 0;
	int	quote;
	char	**array;
	char	*input;
	
	input = strtrim_space(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	while (input && input[count] != '\0')
	{
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
		else if (!is_space(input[start]))
		{
			while (input[count] != '\0' && !is_metachar(input[count]) && !is_quote(input[count]))
				count++;
		}
		array[token++] = substr_by_address(&input[start], (count - start));
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	array[token] = NULL;
	free(input);
	return (array);
}

// int	main(void)
// {
// 	// int	i = 0;
// 	char	*input = "token 1 2 '3' << | >| >> '    50 |>'";
// 	char	**tokens;
// 	
// 	tokens = get_tokens(input);
// 	free_split(tokens);
// 	return (0);
// }
