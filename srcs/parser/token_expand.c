#include "../../includes/minishell.h"

t_tab	*get_cmdtable(char **input, t_env *env)
{
	int	i = 0;
	t_list	*list;
	t_tab	*cmdtable;

	list = new_list(&input[i]);
	cmdtable = malloc(sizeof(t_tab));
	cmdtable->head = list;
	cmdtable->len = 1;
	list = list->next;
	i += cmdlen(&input[i]);
	while (input[i] != NULL)
	{
		list = new_list(&input[i]);
		add_list(list, cmdtable);
		i += cmdlen(&input[i]);
		cmdtable->len++;
	}
	identify_tokens(cmdtable);
	// expand(cmdtable, env);
	// rm_quotes(cmdtable);
	return (cmdtable);
}

int	is_name(char c)
{
	return ((c == '_') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	strvar(char *str)
{
	int	squote = 0;
	int	i = 0;

	while(str && str[i] != '\0')
	{
		if (str[i] == '\'')
			squote++;
		else if (str[i] == '$' && squote % 2 == 0)
		{
			if (is_name(str[i + 1]) && !is_number(str[i + 1]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	strquote(char *str)
{
	int	squote = 0;
	int	dquote = 0;
	int	i = 0;

	while(str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return(i);
		i++;
	}
	return (-1);
}

void	rm_quote(char *str, int start)
{
	int	i;
	int	count = 1;
	int	quote;
	char	*new_str;

	i = start;
	quote = start;
	while (str[i] != '\0')
	{
		while (str[i] && count % 2 != 0)
		{
			if (str[i] == str[quote])
				count++;
			i++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = i;
			count++;
		}
		i++;
	}
	new_str = malloc((ft_strlen(str) - count + 1) * sizeof(char));
	i = start + 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			while (str[i] && str[i] != str[start])
				i++;
			ft_strlcat(new_str, &str[start + 1], i - 1);
		}
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		i++;
	}
}

t_envnode	*get_var(char *str, t_env *env)
{
	int	i = 1;
	int	e = 1;
	t_envnode	*node;

	node = env->head;
	while (str && is_name(str[i]) && node != NULL)
	{
		while (is_name(str[i]) && str[i] == node->key[e])
		{
			i++;
			e++;
		}
		if (is_name(str[i]) && str[i] != node->key[e])
		{
			i = 1;
			e = 0;
			node = node->next;
		}
	}
	if (node == NULL)
		return (NULL);
	return (node);
}

void	expand(t_node *token, t_env *env, int start)
{
	t_envnode	*node;
	int	new_len;
	int	key_len;
	int	val_len;
	char	*new_val;

	node = get_var(&token->value[start], env);
	// if (!node)
		//expand to nothing
	key_len = ft_strlen(node->key) + 1;
	val_len = ft_strlen(node->value);
	new_len = ft_strlen(token->value) - key_len + val_len + 1;
	new_val = malloc(new_len * sizeof(char));
	if (start > 0)
		ft_strlcpy(new_val, token->value, start);
	ft_strlcat(new_val, node->value, val_len);
	start += key_len;
	if (&token->value[start])
		ft_strlcat(new_val, &token->value[start], ft_strlen(&token->value[start]));
	free(token->value);
}

void	format(t_tab *cmdtable, t_env *env)
{
	int	var = 0;
	int	quote = 0;
	t_list	*cmd;
	t_node	*token;
	
	cmd = cmdtable->head;
	token = cmd->head;
	while (cmd != NULL)
	{
		var = strvar(&token->value[var++]);
		while (var >= 0)
		{
			expand(token, env, var);
			var = strvar(&token->value[var++]);
		}
		quote = strquote(token->value);
		rm_quote(token, quote);
		token = token->next;
		if (token == NULL)
			cmd = cmd->next;
	}
}

// void	walk_cmtable(t_tab *cmdtable)
// {
// 	t_list	*cmd;
// 	t_node	*tok;
// 	
// 	cmd = cmdtable->head;
// 	tok = cmd->head;
// 	while (cmd != NULL)
// 	{
// 		tok = tok->next;
// 		if (tok == NULL)
// 		{
// 			cmd = cmd->next;
// 		}
// 	}
// }
