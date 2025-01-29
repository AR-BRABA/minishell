#include "../../includes/minishell.h"

void	rm_quote(t_node *token)
{
	int	i = 0;
	int	q = 0;
	char	*unquoted;
	int	len[2] = {ft_strlen(token->value), strlen_unquote(token->value)};
	int	quote[2] = {0, 0};

	if (len[0] == len[1])
		return ;
	unquoted = malloc((len[1] + 1) * sizeof(char));
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '\'' && quote[1] % 2 == 0)
			quote[0]++;
		else if (token->value[i] == '\"' && quote[0] % 2 == 0)
			quote[1]++;
		else
			unquoted[q++] = token->value[i];
		i++;
	}
	unquoted[q] = '\0';
	free(token->value);
	token->value = unquoted;
}

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
	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char)); // leak
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

/* search for '$' outside single quotes, if whats next is a valid env var name, searchs for it on env list. if found: the key is replaced by its value, else: its expanded to nothing. */
void	expand(t_node *token, t_env *env)
{
	char	*expanded = NULL;
	char	*str = token->value;
	char	*var;
	t_envnode	*node;

	while ((var = strchr(str, '$')))
	{
		expanded = ft_strnjoin(expanded, str, var - str);
		var++;
		char *end = var;
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
		char *key = strndup(var, end - var);
		node = search_key(env, key);
		free(key);
		if (node)
			expanded = ft_strfjoin(expanded, node->value);
		str = end;
	}
	expanded = ft_strfjoin(expanded, str);
	free(token->value);
	token->value = expanded;
}

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