#include "../../includes/minishell.h"

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

void	build_unquoted(char *quoted, char *unquoted)
{
	int	squote;
	int	dquote;
	int	i;
	int	q;

	squote = 0;
	dquote = 0;
	i = 0;
	q = 0;
	while (quoted[i] != '\0')
	{
		if ((quoted[i] == '\'' && dquote % 2 == 0) || (quoted[i] == '\"'
				&& squote % 2 == 0))
		{
			if (quoted[i] == '\'')
				squote++;
			else
				dquote++;
			i++;
		}
		else
			unquoted[q++] = quoted[i++];
	}
	unquoted[q] = '\0';
}

/* tira aspas externas do token->value */
void	rm_quote(t_node *token)
{
	int		new_len;
	int		len;
	char	*unquoted;

	new_len = strlen_unquote(token->value);
	len = ft_strlen(token->value);
	if (len == new_len)
		return ;
	unquoted = malloc((len + 1) * sizeof(char));
	build_unquoted(token->value, unquoted);
	free(token->value);
	token->value = unquoted;
}

/* search key on env list. returna an env node with key and value,
	if found. else: NULL. free key*/
t_envnode	*search_key(t_env *list, char *key)
{
	int			keylen;
	t_envnode	*env;

	keylen = ft_strlen(key);
	env = list->head;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, keylen + 1) == 0)
			break ;
		env = env->next;
	}
	return (env);
}

/* returns $ position if found outside simple quote. else: -1 */
int	strdol(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '$')
			if (str[i + 1] == '?' || (is_name(str[i + 1]) && !ft_isdigit(str[i
						+ 1])))
				return (i);
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
	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	s_pos = 0;
	while (s1 && s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2 && s2[s_pos] != '\0')
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	free(s1);
	return (s);
}

char	*get_variable_value(t_env *env, char *var, int varlen)
{
	char		*hold;
	t_envnode	*node;

	hold = strndup(var + 1, varlen - 1);
	node = search_key(env, hold);
	free(hold);
	if (node)
		return (node->value);
	return (NULL);
}

int	decide_expansion(char *str, int dol, char *tmp)
{
	int	i;
	int	squote;
	int	dquote;
	int	expansion;

	i = 0;
	squote = 2;
	dquote = 2;
	expansion = &str[dol] - tmp;
	while (tmp && tmp[i] && i <= expansion)
	{
		if (tmp[i] == '\"')
			dquote++;
		if (tmp[i] == '\'')
			squote++;
		else if (tmp[i] == '$')
			if ((squote % 2 == 0 && dquote % 2 == 0) || dquote % 2 != 0)
				if (tmp[i + 1] == '?' || (is_name(tmp[i + 1])
						&& !ft_isdigit(tmp[i + 1])))
					return (i);
		i++;
	}
	return (-1);
}

char	*expand_variable(char *expanded, char *str, t_env *env)
{
	char	*tmp;
	int		dol;
	int		varlen;
	char	*var;
	char	*value;

	tmp = str;
	dol = strdol(str);
	while (str && dol >= 0 && decide_expansion(str, dol, tmp) >= 0)
	{
		var = str + dol;
		varlen = strlen_isname(var);
		expanded = ft_strnjoin(expanded, str, (var - str));
		if (tecno_status != -24)
			value = ft_itoa(tecno_status);
		else
			value = get_variable_value(env, var, varlen);
		if (value)
			expanded = ft_strfjoin(expanded, value);
		if (tecno_status != -24)
			free(value);
		str += (var - str) + varlen;
		dol = strdol(str);
	}
	return (ft_strfjoin(expanded, str));
}

void	expand(t_node *token, t_env *env)
{
	char	*expanded;

	expanded = expand_variable(NULL, token->value, env);
	free(token->value);
	token->value = expanded;
}

/* if not a heredoc delimiter, expands all variables that may exist. next,
	removes outside quotes that may exist */
void	format(t_tab *cmdtable, t_env *env)
{
	t_list	*cmd;
	t_node	*token;

	(void)env;
	cmd = cmdtable->head;
	token = cmd->head;
	if (!token)
		return ;
	while (cmd != NULL && token != NULL)
	{
		if (token->type != HEREDOC_DELIMITER)
			expand(token, env);
		rm_quote(token);
		token = token->next;
		if (token == NULL)
		{
			cmd = cmd->next;
			if (cmd == NULL)
				break ;
			token = cmd->head;
		}
	}
}
