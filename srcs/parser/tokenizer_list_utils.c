/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:40:59 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 15:41:01 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	cmdtable->len++;
}

t_node	*new_node(char *token)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	if (!cmd)
		return (NULL);
	cmd->value = token;
	cmd->type = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_list	*new_list(char **input)
{
	int		i;
	t_list	*cmdlist;
	t_node	*cmd;

	cmdlist = init_cmdlist(input);
	if (!cmdlist)
		return (NULL);
	i = 1;
	while (input[i] != NULL)
	{
		cmd = new_node(input[i]);
		if (!cmd)
		{
			free_list(cmdlist);
			return (NULL);
		}
		add_node(cmd, cmdlist);
		cmdlist->len++;
		if (input[i] && input[i][0] == '|')
			break ;
		i++;
	}
	return (cmdlist);
}
