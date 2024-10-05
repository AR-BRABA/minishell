#include "../../includes/minishell.h"

/* returns if is a valid name for an enviroment variable ([a-z], [A-Z], '_', [0-9]) */
int	is_name(char c)
{
	return ((c == '_') || ft_isalnum(c));
}

/* strlen while is a valid name for an enviroment variable ([a-z], [A-Z], '_', [0-9] except on index 0, '?') */
int	strlen_isname(char *str)
{
	int	i = 1;
	//
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
	int	i = start;
//
	while(str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return(i);
		i++;
	}
	return (-1);
}

/* takes a quoted str as parameter and returns it's len without outside quotes */
int	strlen_unquote(char *quotestr)
{
	int	i = 0;
	int	start = 0;
	int	quote = 0;
//
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
	printf("\nstrlen - quote = %i\n", (i - quote));
	return (i - quote);
}

/* tira aspas externas do token->value */
void	rm_quote(t_node *token)
{
	int	squote = 0;
	int	dquote = 0;
	int	i = 0;
	int	q = 0;
	int	new_len = strlen_unquote(token->value);
	int	len = ft_strlen(token->value);
	char	*unquoted;
//
	if (len == new_len)
		return ;
	unquoted = malloc((new_len + 1) * sizeof(char));
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '\'')
		{
			if (dquote % 2 != 0)
				unquoted[q++] = token->value[i++];
			else
			{
				squote++;
				i++;
			}
		}	
		else if (token->value[i] == '\"')
		{
			if (squote % 2 != 0)
				unquoted[q++] = token->value[i++];
			else
			{
				dquote++;
				i++;
			}
		}
		else
			unquoted[q++] = token->value[i++];
	}
	unquoted[q] = '\0';
	free(token->value);
	token->value = unquoted;
}

/* search key on env list. returna an env node with key and value, if found. else: NULL. free key*/
t_envnode	*search_key(t_env *list, char *key)
{
	int	keylen = ft_strlen(key);
	t_envnode	*env;

	env = list->head;
	while (env != NULL)
	{
		//compare key with env variables on list
		if (ft_strncmp(key, env->key, keylen) == 0)
			break ;
		env = env->next;

	i = ft_strlen(s);
	if (!s || n <= 0 || i < n)
		return (NULL);
	dest = (char *) malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* returns $ position if found outside simple quote. else: -1 */
int	strdol(char *str)
{
	int	squote = 0;
	int	i = 0;
//
	while(str && str[i] != '\0')
	{
		if (str[i] == '\'')
			squote++;
		else if (str[i] == '$' && squote % 2 == 0)
			if (str[i + 1] == '?' || (is_name(str[i + 1]) && !ft_isdigit(str[i + 1])))
				return (i) ;
		i++;
	}
	return (-1);
}

/* join s1 and s2 into return string until n bytes and free s1*/
char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*s;
	int		i;
	int		s_pos;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	s_pos = 0;
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2 && s2[s_pos] != '\0' && s_pos < n)
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	free(s1);
	return (s);
}

/* join s1 and s2 into return string and free s1*/
char	*ft_strfjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		s_pos;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	s_pos = 0;
	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2 && s2[s_pos] != '\0')
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	free(s1);
	return (s);
}

/* search for '$' outside single quotes, if whats next is a valid env var name, searchs for it on env list. if found: the key is replaced by its value, else: its expanded to nothing. */
void	expand(t_node *token, t_env *env)
{
	int	varlen;
	char	*expanded;
	t_envnode	*node;
	char	*str;
	char	*var;
	int	dol;
// //
	str = token->value;
	while (str)
	{
		//dol = index of next $ followed by a valid char. if not found, = -1
		dol = strdol(str);
		if (dol < 0)
			break ;
		// var = a pointer to '$' on str. (by incrementing str to '$' index)
		var = str + dol;
		// varlen = strlen while is a valid name, starting on '$'
		varlen = strlen_isname(var);
		// expanded = expanded + content before '$', if there is
		expanded = ft_strnjoin(expanded, str, (var - str)); // free on
		// node = node on env list matching var with node->key. if not found, NULL
		node = search_key(env, strndup(var + 1, varlen - 1)); //free na key on
		// if found, expanded = expanded + value of the matching key
		if (node)
			expanded = ft_strfjoin(expanded, node->value); // free on
		// increments str pointer to after var ends
		str += (var - str) + varlen;
	}
	// adds content that may be after expanding all existing variables
	expanded = ft_strfjoin(expanded, str);
	free(token->value);
	token->value = expanded;
}

/* if not a heredoc delimiter, expands all variables that may exist. next, removes outside quotes that may exist */
void	format(t_tab *cmdtable, t_env *env)
{
	t_list	*cmd;
	t_node	*token;
	//
	(void)env;
	cmd = cmdtable->head;
	token = cmd->head;
	if (!token)
		return ; //barrar na validacao inicial inputs vazios
	// percorrendo cmd table
	while (cmd != NULL)
	{
		// se nao for um delimitador de heredoc, expande todas as variaveis desse token
		if (!(token->type == REDIRECT_FILE && token->prev && token->prev->type == HEREDOC))
			expand(token, env);
		// removes outside quotes
		rm_quote(token);
		token = token->next;
		if (token == NULL)
			cmd = cmd->next;
	}
}
