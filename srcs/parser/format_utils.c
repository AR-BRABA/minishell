#include "../../includes/minishell.h"

/* returns $ position if found outside simple quote. else: -1 */
int	strdol(char *str)
{
	int	squote;
	int	i;

	squote = 0;
	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'')
			squote++;
		else if (str[i] == '$' && squote % 2 == 0)
			if (str[i + 1] == '?' || (is_name(str[i + 1]) && !ft_isdigit(str[i
						+ 1])))
				return (i);
		i++;
	}
	return (-1);
}

/* strlen while is a valid name for an enviroment variable ([a-z], [A-Z], '_',
		[0-9] except on index 0, '?') */
int	strlen_isname(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '?')
		return (++i);
	while (str[i] && is_name(str[i]))
		i++;
	return (i);
}

/* returns index of the first quote found. if not found, returns -1 */
int	strquote(char *str, int start)
{
	int	i;

	i = start;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

/* takes a quoted str as parameter and returns it's len without outside quotes */
int	strlen_unquote(char *quotestr)
{
	int	i;
	int	start;
	int	quote;

	i = 0;
	start = 0;
	quote = 0;
	while (quotestr && quotestr[i] != '\0')
	{
		if (quotestr[i] == '\'' || quotestr[i] == '"')
		{
			quote++;
			start = i++;
			while (quotestr[i] && quotestr[i] != quotestr[start])
				i++;
			quote++;
		}
		i++;
	}
	return (i - quote);
}
