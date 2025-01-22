#include "../../includes/minishell.h"

void	build_unquoted(int len, char *quoted, char *unquoted)
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
	build_unquoted(new_len, token->value, unquoted);
	free(token->value);
	token->value = unquoted;
}

/* tira aspas externas do token->value */
/* void	rm_quote(t_node *token) */
/* { */
/* 	int		squote; */
/* 	int		dquote; */
/* 	int		i; */
/* 	int		q; */
/* 	int		new_len; */
/* 	int		len; */
/* 	char	*unquoted; */
/**/
/* 	squote = 0; */
/* 	dquote = 0; */
/* 	i = 0; */
/* 	q = 0; */
/* 	new_len = strlen_unquote(token->value); */
/* 	len = ft_strlen(token->value); */
/* 	if (len == new_len) */
/* 		return ; */
/* 	unquoted = malloc((new_len + 1) * sizeof(char)); */
/* 	while (token->value[i] != '\0') */
/* 	{ */
/* 		if (token->value[i] == '\'') */
/* 		{ */
/* 			if (dquote % 2 != 0) */
/* 				unquoted[q++] = token->value[i++]; */
/* 			else */
/* 			{ */
/* 				squote++; */
/* 				i++; */
/* 			} */
/* 		} */
/* 		else if (token->value[i] == '\"') */
/* 		{ */
/* 			if (squote % 2 != 0) */
/* 				unquoted[q++] = token->value[i++]; */
/* 			else */
/* 			{ */
/* 				dquote++; */
/* 				i++; */
/* 			} */
/* 		} */
/* 		else */
/* 			unquoted[q++] = token->value[i++]; */
/* 	} */
/* 	unquoted[q] = '\0'; */
/* 	free(token->value); */
/* 	token->value = unquoted; */
/* } */

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

/* search for '$' outside single quotes, if whats next is a valid env var name,
	searchs for it on env list. if found: the key is replaced by its value,
	else: its expanded to nothing. */
void	expand(t_node *token, t_env *env)
{
	char		*expanded;
	t_envnode	*node;
	char		*str;
	char		*var;
	int			dol;

	str = token->value;
	expanded = NULL;
	while (str)
	{
		dol = strdol(str);
		if (dol < 0)
			break ;
		var = str + dol;
		// expanded = ft_strnjoin(expanded, str, (var - str)); // free on
		expanded = ft_substr(str, 0, (var - str));
		node = search_key(env, strndup(var + 1, strlen_isname(var) - 1));
		if (node)
			expanded = ft_strfjoin(expanded, node->value); // free on
		str += (var - str) + strlen_isname(var);
	}
	expanded = ft_strfjoin(expanded, str);
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
