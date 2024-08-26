#include "../../includes/minishell.h"

void	get_redirect_type(t_node *token)
{
	if (token->value[0] == '<' && token->value[1] == '<')
		token->type = HEREDOC;
	else if (token->value[0] == '>' && token->value[1] == '>')
		token->type = APPEND;
	else if (token->value[0] == '<' && token->value[1] == '\0')
		token->type = REDIRECT_IN;
	else if (token->value[0] == '>' && token->value[1] == '\0')
		token->type = REDIRECT_OUT;
	token->next->type = REDIRECT_FILE;
}

void	get_type(t_node *token)
{
	if (token->prev == NULL || token->prev->value[0] == '|')
	{
		if (token->value[0] == '<' || token->value[0] == '>')
			get_redirect_type(token);
		else
			token->type = COMMAND;
	}
	else if (token->value[0] == '|')
		token->type = PIPE;
	else if (token->value[0] == '<' || token->value[0] == '>')
		get_redirect_type(token);
	else
		token->type = ARG;
}

void	identify_tokens(t_tab *cmdtable)
{
	t_list	*cmdline;
	t_node	*token;
	
	cmdline = cmdtable->head;
	token = cmdline->head;
	while (cmdline != NULL && token != NULL)
	{
		if (token->type == -1)
			get_type(token);
		token = token->next;
		if (token == NULL)
		{
			cmdline = cmdline->next;
			if (cmdline == NULL)
				break ;
			token = cmdline->head;
		}
	}
}

t_tab	*get_cmdtable(char **input)
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
	// format(cmdtable);
	return (cmdtable);
}

//TODO: test
//protect malloc
/*
char	*get_key(char *token)
{
	int	i = 1;
	char	*key;

	// if (token[i] >= 0 && token[i] <= 9)
	while (token[i] != '\0' && !is_metachar(token[i]))
		i++;
	key = ft_strndup(&token[0], i); // com $
	return (key);
}

char	*get_key_value(char *key)
{
	

}

int	expanded_strlen(char *token, t_env *env)
{
	int	squote = 2;
	int	varlen = 0;
	int	keylen = 0;
	int	i = 0;
	char	*key;
	// char	*value;

	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			key = get_key(&token[i]);
			keylen += ft_strlen(key);
			vallen += count_key_value(&key[1], env);
			i += ft_strlen(key);
			free(key);
		}
		i++;
	}
	return (varlen + (i - keylen));
}

void	expand_var(char *token)
{
	int	squote = 2;
	int	i = 0;
	int	count;
	char	*key;
	char	*newtok;

	newtok = malloc((expanded_strlen(token) + 1) * sizeof(char));
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			key = get_key(&token[i]);
			ft_strcat(newtok, get_key_value(&key[1]));
			count += count_key_val(&key[1]);
			i += ft_strlen(key);
			free(key);
		}
		newtok[count++] = token[i++];
	}
	free(token);
}

void	remove_quote(t_node *token)
{
	int	i = 0;
	int	squote = 0;
	int	dquote = 0;

	while ()

}
*/
int	main(int argc, char **argv)
{
	char	**input;
	t_tab	*cmdtable;

	input = metachar_split(argv[1]);
	print_split(input);
	cmdtable = get_cmdtable(input);
	print_tab(cmdtable);
	free(input);
	(void)argc;
	return(0);
}
