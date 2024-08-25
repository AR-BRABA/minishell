#include "../../includes/minishell.h"

int	cmdlen(char **input)
{
	int	i = 0;

	while (input[i][0] != '|' && input[i] != NULL)
		i++;
	return(i + 1);
}

enum e_type {
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_FILE,
	APPEND,
	HEREDOC,
};

typedef struct	s_node {
	char	*value;
	int	type;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct	s_list {
	int	len;
	t_node	*head;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

void	add_node(t_node *new, t_node *list)
{
	int	count = 0;
	t_node	*node;
	
	node = list;
	if (!node)
		node = NULL;
	while (node != NULL && node->next != NULL)
		node = node->next;
	node->next = new;
	new->prev = node;
	new->next = NULL;
}

void	add_list(t_list *new, t_list *tab)
{
	int	count = 0;
	t_list	*list;
	
	list = tab;
	if (!list)
		list = NULL;
	while (list != NULL && list->next != NULL)
		list = list->next;
	list->next = new;
	new->prev = list;
	new->next = NULL;
}

t_node	*new_node(char *token)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	cmd->value = token; //dup??
	cmd->type = -1;
	cmd->prev = NULL;
	cmd->next = NULL;

	return (cmd);
}

t_list	*new_list(char **input)
{
	int	i = 0;
	t_node	*cmd;
	t_list	*cmdlist;

	cmdlist = malloc(sizeof(t_list));
	cmdlist->len = 0;
	cmdlist->prev = NULL;
	cmdlist->next = NULL;
	while (input[i] != NULL)
	{
		add_node(new_node(input[i]), cmdlist->head);
		i++;
		cmdlist->len++;
		if (input[i] && input[i][0] == '|')
			break ;
	}
	return (cmdlist);
}

void	get_type(t_node *token)
{
	if (token->prev == NULL || token->prev->value[0] == '|')
		token->type = COMMAND;
	else if (token->value[0] == '|')
		token->type = PIPE;
	else if (token->value[0] == '<' || token->value[0] == '>')
	{
		if (token->value[0] == '<' && token->value[1] == '<')
			token->type = HEREDOC; //delimitador!!
		else if (token->value[0] == '>' && token->value[1] == '>')
			token->type = APPEND;
		else if (token->value[0] == '<' && token->value[1] == '\0')
			token->type = REDIRECT_IN;
		else if (token->value[0] == '>' && token->value[1] == '\0')
			token->type = REDIRECT_OUT;
		token->next->type = REDIRECT_FILE;
	}
	else
		token->type = ARG;
}

void	identify_tokens(t_list *cmdtable)
{
	int	index = 0;
	t_list	*cmdline;
	t_node	*token;
	
	cmdline = cmdtable;
	token = cmdline->head;
	while (cmdline != NULL && token != NULL)
	{
		if (token->type == -1)
			get_type(token);
		// if (token->type <= FD)
		// {
		// 	expand_var(token->value);
		// 	remove_quote(token->value);
		// }
		// em outra func
		token = token->next;
		if (token == NULL)
		{
			cmdline = cmdline->next;
			token = cmdline->head;
		}
	}
}

t_list	*get_cmdtable(char **input)
{
	int	i = 0;
	int	cmd = 0;
	t_list	*cmdtable;

	while (input[i] != NULL)
	{
		add_list(new_list(&input[i]), cmdtable);
		i += cmdlen(&input[i]);
	}
	identify_tokens(cmdtable);
	// format(cmdtable);
	return (cmdtable);
}

/*
int	count_varlen(char *token)
{

}

char	*get_key(char *token)
{
	int	i = 0;

	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			i++;
			
		}
	}
}

char	*get_key_value(char *token)
{

}

int	expanded_strlen(char *token)
{
	int	squote = 2;
	int	varlen = 0;
	int	i = 0;

	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			//pegar key pra achar var (usar a outra func de molde)
			varlen += count_varlen(&token[i]);
			while (token[i] && token[i] != ' ') //enquanto for key -eh key ate o final ou espaco?
				i++;
		}
		i++;
	}
	return (varlen + i);
}

void	expand_var(char *token)
{
	int	squote = 2;
	int	i = 0;
	int	count;
	char	*key;
	char	*newval;

	newval = malloc((expanded_strlen(token) + 1) * sizeof(char));
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			key = get_key(&token[i]);
			ft_strcat(newval[count], get_key_value(key));
			while (*key++)
				i++;
		}
		newval[count++] = token[i++];
	}
	free(token); //tem q dar o free no char ** -- mudar isso, fazer 1 dup
	token = newval;
}

void	remove_quote(t_node *token)
{
	int	i = 0;
	int	squote = 0;
	int	dquote = 0;

	while ()

}
*/
