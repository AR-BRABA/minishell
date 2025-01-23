#include "../../includes/minishell.h"

void	set_redirect_type(t_node *token)
{
	if (token->value[0] == '<' && token->value[1] == '<')
		token->type = HEREDOC;
	else if (token->value[0] == '>' && token->value[1] == '>')
		token->type = APPEND;
	else if (token->value[0] == '<' && token->value[1] == '\0')
		token->type = REDIRECT_IN;
	else if (token->value[0] == '>' && token->value[1] == '\0')
		token->type = REDIRECT_OUT;
	if (token->type == APPEND || token->type == REDIRECT_OUT)
		token->next->type = OUT_FILE;
	else if (token->type == REDIRECT_IN)
		token->next->type = IN_FILE;
	else if (token->type == HEREDOC)
		token->next->type = HEREDOC_DELIMITER;
}

void	set_type(t_node *token)
{
	if (token->prev == NULL || token->prev->value[0] == '|')
	{
		if (token->value[0] == '<' || token->value[0] == '>')
			set_redirect_type(token);
		else
			token->type = COMMAND;
	}
	else if (token->value[0] == '|')
		token->type = PIPE;
	else if (token->value[0] == '<' || token->value[0] == '>')
		set_redirect_type(token);
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
			set_type(token);
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

t_tab	*init_cmdtab(char **input)
{
	int		i;
	t_list	*list;
	t_tab	*cmdtable;

	i = 0;
	if (!input)
		return (NULL);
	list = new_list(&input[i]);
	if (!list)
		return (NULL);
	cmdtable = malloc(sizeof(t_tab));
	if (!cmdtable)
	{
		free_list(list);
		return (NULL);
	}
	cmdtable->head = list;
	cmdtable->len = 1;
	return (cmdtable);
}
