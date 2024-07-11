#include "../includes/minishell.h"

int	count_tokens(char *input)
{
	int	count = 0;
	int	start = 0;
	int	tokens = 0;

	while (input && input[count] != '\0')
	{
		start = count;
		count++;
		if (is_operator(input[start]))
		{
			if (is_operator(input[count]) && input[count] == input[start])
				count++;
		}
		else if (is_quote(input[start]))
		{
			while (input[count] != '\0' && input[count] != input[start])
				count++;
			count++;
		}
		else if (is_basic(input[start]))
		{
			while (input[count] != '\0' && is_basic(input[count]))
				count++;
		}
		tokens++;
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	return (tokens);
}

char	**tokenizer(char *user_input)
{
	int	count = 0;
	int	start = 0;
	int	token = 0;
	char	**array;
	char	*input;
	
	// expansao de variaveis? ver no futuro
	// $
	input = strtrim_space(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	// printf("\n\ntokens + null = %i\n\n\n", count_tokens(input));
	while (input && input[count] != '\0')
	{
		start = count;
		count++;
		if (is_operator(input[start]))
		{
			if (is_operator(input[count]) && input[count] == input[start])
			// se eh especial (<,|,>) e se o proximo eh igual (>>, <<)
			{
				count++;
			}
		}
		else if (is_quote(input[start]))
		{
			while (input[count] != '\0' && input[count] != input[start])
			{
				count++;
			}
			count++;
		}
		else if (is_basic(input[start]))
		{
			while (input[count] != '\0' && is_basic(input[count]))
			{
				count++;
			}
		}
		array[token++] = substr_by_address(&input[start], (count - start));
		// printf("\ntoken%i - count: %i | start: %i\n\n", token, count, start);
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
// 	int	i = 0;
// 	char	*input = "token 1 2 '3' << | >| >> '    50 |>'";
// 	char	**tokens;
// 	
// 	tokens = tokenizer(input);
// 	free_split(tokens);
// 	return (0);
// }
