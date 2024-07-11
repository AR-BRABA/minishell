#include "../includes/minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_basic(char c)
{
	return (!(is_special(c)) && !(is_quote(c)) && !(is_space(c)));
}

int	count_tokens(char *input)
{
	int	count = 0;
	int	start = 0;
	int	tokens = 0;

	while (input && input[count] != '\0')
	{
		start = count;
		count++;
		if (is_special(input[start]))
		{
			if (is_special(input[count]) && input[count] == input[start])
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
		if (is_special(input[start]))
		{
			if (is_special(input[count]) && input[count] == input[start])
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
		array[token++] = ft_substr(&input[start], (count - start));
		// printf("\ntoken%i - count: %i | start: %i\n\n", token, count, start);
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	array[token] = NULL;
	free(input);
	return (array);
}

void	free_split(char **array)
{
	int	i = 0;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_split(char **array)
{
	int	i = 0;

	while (array[i] != NULL)
	{
		printf("%d: <%s>\n", i, array[i]);
		i++;
	}
}

int	main(void)
{
	int	i = 0;
	char	*input = "token 1 2 '3' << | >| >> '    50 |>'";
	char	**tokens;
	
	tokens = tokenizer(input);
	free_split(tokens);
	return (0);
}
