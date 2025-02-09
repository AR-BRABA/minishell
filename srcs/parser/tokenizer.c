/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:26:02 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/09 05:16:04 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_command(t_node *token)
{
	t_node	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->value[0] == '<' || tmp->value[0] == '>')
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
		}
		else
		{
			tmp->type = COMMAND;
			return ;
		}
	}
}

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
	if (token->type == APPEND || token->type == REDIRECT_OUT)
	{
		if (token->next->type)
			token->next->type = OUT_FILE;
	}
	else if (token->type == REDIRECT_IN)
	{
		if (token->next->type)
			token->next->type = IN_FILE;
	}
	else if (token->type == HEREDOC)
	{
		if (token->next->type)
			token->next->type = HEREDOC_DELIMITER;
	}
}

void	get_type(t_node *token)
{
	if (token->prev == NULL || token->prev->value[0] == '|')
	{
		if (token->value[0] == '<' || token->value[0] == '>')
			get_redirect_type(token);
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
	find_command(token);
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

t_tab	*get_cmdtable(char **input, t_env *env)
{
	int		i;
	t_list	*list;
	t_tab	*cmdtable;

	i = 0;
	cmdtable = init_cmdtab(input);
	if (!cmdtable)
		return (NULL);
	i += cmdlen(input);
	while (input[i] != NULL)
	{
		list = new_list(&input[i]);
		if (!list)
		{
			free_list(list);
			free_table(cmdtable);
			return (NULL);
		}
		add_list(list, cmdtable);
		i += cmdlen(&input[i]);
	}
	identify_tokens(cmdtable);
	format(cmdtable, env);
	return (cmdtable);
}
