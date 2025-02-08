/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:26:10 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 10:26:12 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmdlen(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL && input[i][0] != '|')
		i++;
	if (input[i] != NULL && input[i][0] == '|')
		i++;
	return (i);
}

t_list	*init_cmdlist(char **input)
{
	t_list	*cmdlist;
	t_node	*cmd;

	cmdlist = malloc(sizeof(t_list));
	if (!cmdlist)
		return (NULL);
	cmdlist->fd[0] = 0;
	cmdlist->fd[1] = 1;
	cmdlist->prev = NULL;
	cmdlist->next = NULL;
	cmd = new_node(input[0]);
	if (!cmd)
	{
		free_list(cmdlist);
		return (NULL);
	}
	cmdlist->head = cmd;
	cmdlist->len = 1;
	return (cmdlist);
}
