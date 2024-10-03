#include "../../includes/minishell.h"

int	is_name(char c)
{
	return ((c == '_') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	strlen_isname(char *str)
{
	int	i = 1;
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

// /* returns $ position if found outside simple quote, else: -1 */
// char	*get_next_var(char *str)
// {
// 	int	squote = 0;
// 	int	start;
// 	int	end;
// 	char	*key;
// //
// 	while(str && str[start] != '\0')
// 	{
// 		if (str[start] == '\'')
// 			squote++;
// 		else if (str[start] == '$' && squote % 2 == 0)
// 			if (str[start + 1] == '?' || (is_name(str[start + 1]) && !is_number(str[start + 1])))
// 				break ;
// 		start++;
// 	}
// 	key = ft_strndup(&str[start], strlen_isname(&str[start]));
// 	return (key);
// }

/* retorna um ponteiro para a proxima var no token->value */
char	*get_next_var(char *token)
{
	static char	*var;
	int	varlen;
//
	if (!var)
		var = token;
	else
		var++;
	while (var)
	{
		var = strchr(var, '$');
		varlen = strlen_isname(var);
		if (varlen <= 1)
			*var += varlen;
		else
			return (var);
	}
	return (NULL);
}

// heredoc $? $$
void	expand(t_node *token, t_env *env, char *var)
{
	int	newlen;
	int	varlen;
	char	*expanded;
	t_envnode	*node;
	char	*str;
// //
	str = token->value;
	varlen = strlen_isname(var);
	var = strndup(var, varlen);
	node = search_key(env, var);
	if (node)
		newlen = ft_strlen(node->value);
	else
		newlen = 0;
	expanded = malloc((ft_strlen(str) - varlen + newlen + 1) * sizeof(char));
	ft_strlcpy(expanded, str, (*var - *str));
	if (node)
		ft_strlcat(expanded, node->value, newlen);
	*str += *var + varlen;
	ft_strlcat(expanded, str, ft_strlen(str));
	free(token->value);
	token->value = expanded;
}

void	format(t_tab *cmdtable, t_env *env)
{
	char	*var;
	t_list	*cmd;
	t_node	*token;
	//
	(void)env;
	cmd = cmdtable->head;
	token = cmd->head;
	while (cmd != NULL)
	{
		var = get_next_var(token->value);
		while (var) //segfault? HEREDOCCCCCCCCC
		{
			expand(token, env, var);
			var = get_next_var(token->value);
		}
		rm_quote(token);
		token = token->next;
		if (token == NULL)
			cmd = cmd->next;
	}
}
