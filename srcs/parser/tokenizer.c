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
