#include "../../includes/minishell.h"

int	cmdlen(char **input)
{
	int	i = 0;

	while (input[i] != NULL && input[i][0] != '|')
		i++;
	if (input[i] != NULL && input[i][0] == '|')
		i++;
	return(i);
}

void	add_node(t_node *newnode, t_list *list)
{
	t_node	*node;
	
	node = list->head;
	if (!node)
		list->head = newnode;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = newnode;
		newnode->prev = node;
	}
}

void	add_list(t_list *newnode, t_tab *cmdtable)
{
	t_list	*list;
	
	list = cmdtable->head;
	if (!list)
		cmdtable->head = newnode;
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = newnode;
		newnode->prev = list;
	}
}

t_node	*new_node(char *token)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	cmd->value = token;
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
		cmd = new_node(input[i]);
		add_node(cmd, cmdlist);
		cmdlist->len++;
		if (input[i] && input[i][0] == '|')
			break ;
		i++;
	}
	return (cmdlist);
}
