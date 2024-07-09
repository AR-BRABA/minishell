#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;
	i = 0;

	while (str && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char *s1)
{
	char	*trim;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && s1[start] == ' ')
		start++;
	while (end > start && s1[end] == ' ')
		end--;
	trim = (char *) malloc((end - start + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	while (start <= end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	free(s1);
	return (trim);
}

char	*ft_substr(char *s, int len)
{
	int	i;
	char	*substr;

	i = 0;
	substr = malloc ((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

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

int	count_tokens(char *user_input)
{
	int	i = 0;
	int	start = 0;
	int	token = 0;

	while (user_input && user_input[i] != '\0')
	{
		start = i;
		if (is_special(user_input[i]))
		{
			i++;
			if (is_special(user_input[i]) && user_input[i] == user_input[i - 1])
			// se eh especial (<,|,>) e se o proximo eh igual (>>, <<)
				i++;
		}
		else if (is_quote(user_input[i]))
		{
			i++;
			while (user_input[i] != '\0' && user_input[i] != user_input[start])
				i++;
		}
		else if (is_basic(user_input[i]))
		{
			i++;
			while (user_input[i] != '\0' && is_basic(user_input[i]))
				i++;
		}
		token++;
		if (is_space(user_input[i]))
			while (is_space(user_input[i]))
				i++;
	}
	return (token);
}

void	tokenizer(char *user_input)
{
	int	count = 0;
	int	start = 0;
	// int	count = 0;
	// char	**tokens;
	
	// expansao de variaveis? ver no futuro
	// $
	// tokens = (char **)malloc(count_tokens(user_input) * sizeof(char *));
	// user_input = ft_strtrim(user_input);
	while (user_input && user_input[count] != '\0')
	{
		start = count;
		printf("%c", user_input[start]);
		count++;
		if (is_special(user_input[start]))
		{
			if (is_special(user_input[count]) && user_input[count] == user_input[start])
			// se eh especial (<,|,>) e se o proximo eh igual (>>, <<)
			{
				printf("%c", user_input[count]);
				count++;
			}
		}
		else if (is_quote(user_input[start]))
		{
			while (user_input[count] != '\0' && user_input[count] != user_input[start])
			{
				printf("%c", user_input[count]);
				count++;
			}
			printf("%c", user_input[count]);
			count++;
		}
		else if (is_basic(user_input[start]))
		{
			while (user_input[count] != '\0' && is_basic(user_input[count]))
			{
				printf("%c", user_input[count]);
				count++;
			}
		}
		// tokens[count++] = ft_substr(&user_input[start], (i - start));
		if (is_space(user_input[count]))
			while (is_space(user_input[count]))
				count++;
		printf("\n");
	}
	// tokens[count] = NULL;
	// falta malloc
	// return (tokens);
}

int	main(int argc, char **argv)
{
	// int	i = 0;
	// char	**tokens;
	
	(void)argv;	
	if (argc < 2)
		return (1);
	tokenizer("teste tokens             aqui 'e 'mais uma'aqui'     << >> |<< |");
	// tokens = tokenizer(argv[1]);
	// while (tokens[i] != NULL)
	// {
	// 	printf("%d: %s\n", i, tokens[i]);
	// 	i++;
	// }
	return (0);
}
