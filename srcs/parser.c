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
	return (c >= 7 && c <= 13);
}

char	**lexer(char *user_input)
{
	int	i = 0;
	int	start = 0;
	int	count = 0;
	char	**tokens;
	
	// expansao de variaveis? ver no futuro
	// $
	// |<< > >>
	//
	// tokens = (char **)malloc(count_tokens(user_input) * sizeof(char *));
	user_input = ft_strtrim(user_input);
	while (user_input && user_input[i] != '\0')
	{
		start = i;
		if (is_special(user_input[i++]))
		{
			if (is_special(user_input[i]))
				i++;
		}
		else if (is_quote(user_input[i++])) // ver se funciona
			while (user_input[i] != user_input[start])
				i++;
		else if (!(is_special(user_input[i])) && !(is_quote(user_input[i])) && !(is_space(user_input[i])) && user_input[i++] != '\0')
			while (user_input[i] != '\0' && !(is_special(user_input[i])) && !(is_quote(user_input[i])) && !(is_space(user_input[i])))
				i++;
		tokens[count++] = ft_substr(&user_input[start], (i - start));
		if (is_space(user_input[i]))
			while (is_space(user_input[i]))
				i++;
	}
	// falta malloc
	return (tokens);
}

int	main(int argc, char **argv)
{
	int	i = 0;
	char	**tokens;

	if (argc < 2)
		return (1);
	tokens = lexer(argv[1]);
	while (tokens[i] != NULL)
	{
		printf("%d: %s\n", i, tokens[i]);
		i++;
	}
	return (0);
}
