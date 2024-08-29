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
			if (str[i + 1] && is_name(str[i + 1]) && !is_number(str[i + 1]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	strquote(char *str)
{
	int	squote = 0;
	int	i = 0;

	while(str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return(i);
		i++;
	}
	return (-1);
}

t_envnode	*find_value(char *str, t_env *env)
{
	int	i = 1;
	int	e = 1;
	t_envnode	*node;
	char	*key;

	node = env->head;
	while (str && str[i] != '\0' && is_name(str[i]) && node != NULL)
	{
		while (str[i] == node->key[e])
		{
			i++;
			e++;
		}
		if (str[i] != node->key[e])
		{
			i = 1;
			e = 1;
			node = node->next;
		}
	}
	if (node == NULL)
		return (NULL);
	else
		return (node);
}

void	expand(t_node *token, t_env *env, int start)
{
	t_envnode	*node;

	node = find_value(&token->value[start], env);
	if (!node)
		//expand to nothing
	//expand to key value
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
		while (var >= 0)
		{
			var = strvar(&token->value[var++]);
			expand(token, env, var);
		}
		while (quote >= 0)
		{
			quote = strquote(token->value);
			rm_quote(token, quote);
		}
		token = token->next;
		if (token == NULL)
		{
			cmd = cmd->next;
		}
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
