#include "../../includes/minishell.h"

int	is_name(char c)
{
	return ((c == '_') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

/* returns $ position if found outside simple quote, else: -1 */
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
			if (str[i + 1] == '?' || (is_name(str[i + 1]) && !is_number(str[i + 1])))
				return (i);
		i++;
	}
	return (-1);
}

int	strlen_isname(char *str)
{
	int	i = 0;
	//
	if (is_number(str[i]) || str[i] == '?')
		return (++i);
	while (str && str[i] != '\0' && is_name(str[i]))
		i++;
	return (i);
}

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
	free(token->value);
	token->value = unquoted;
}

	// while (token->value[i] != '\0')
	// {
	// 	if (token->value[i++] == '\'' && dquote % 2 == 0)
	// 		squote++;
	// 	else if (token->value[i++] == '\"' && squote % 2 == 0)
	// 		dquote++;
	// 	else
	// 		unquoted[q++] = token->value[i++];
	// }

t_envnode	*search_key(t_env *list, char *key)
{
	int	keylen = ft_strlen(key);
	int	envklen;
	t_envnode	*env;

	env = list->head;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, keylen) == 0)
			break ;
		env = env->next;
	}
	if (env)
		envklen = ft_strlen(env->key);
	if ((env && envklen != keylen) || !env) //funciona?
		return (NULL);
	printf("\n\nkey = %s\n", env->key);
	return (env);

}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dest;

	i = ft_strlen(s);
	if (!s || n < 0 || i < n) // i < n ?
		return (NULL);
	dest = (char *) malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i <= n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// heredoc $? $$
void	expand(t_node *token, t_env *env, int start)
{
	int	i = 0;
	int	count = 0;
	int	count2 = 0;
	int	end;
	char	*key;
	char	*expanded;
	t_envnode	*node;
//
	start++;
	end = start + strlen_isname(&token->value[start]) - 1;
	key = ft_strndup(&token->value[start], (end - start));
	node = search_key(env, key);
	start--;
	// func to replace key to node->value on token->value and return char *
	if (node)
		expanded = malloc((ft_strlen(token->value) - (end - start) + ft_strlen(node->value) + 1) * sizeof(char)); // if str == null ft_strlen return = 0?
	else
		expanded = malloc((ft_strlen(token->value) - (end - start) + 1) * sizeof(char)); 
	while (token->value[count] != '\0')
	{
		if (count == start)
		{
			if (node)
			{
				while (node->value[count2] != '\0')
					expanded[i++] = node->value[count2++];
			}
			count = end + 1;
		}
		else
			expanded[i++] = token->value[count++];
	}
	free(token->value);
	token->value = expanded;
}

void	format(t_tab *cmdtable, t_env *env)
{
	int	var = 0;
	t_list	*cmd;
	t_node	*token;
	//
	(void)env;
	cmd = cmdtable->head;
	token = cmd->head;
	while (cmd != NULL)
	{
		var = strdol(&token->value[var++]);
		while (var >= 0) //segfault? HEREDOCCCCCCCCC
		{
			expand(token, env, var);
			var = strdol(&token->value[++var]);
		}
		rm_quote(token);
		token = token->next;
		if (token == NULL)
			cmd = cmd->next;
	}
}
