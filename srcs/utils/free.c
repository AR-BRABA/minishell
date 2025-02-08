/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:34:27 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 10:34:29 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envnode(t_envnode *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_list(t_list *cmdline)
{
	t_node	*token;
	t_node	*tmptoken;

	token = cmdline->head;
	while (token != NULL)
	{
		tmptoken = token->next;
		free(token->value);
		free(token);
		token = tmptoken;
	}
	free(cmdline);
}

int	free_env(t_env *env)
{
	t_envnode	*node;
	t_envnode	*temp;

	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		temp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(env);
	return (0);
}
