/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:11:03 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 13:11:04 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*get_cmd(t_list *cmdlist)
{
	t_node	*token;

	token = cmdlist->head;
	while (token != NULL)
	{
		if (token->type == COMMAND)
			return (token);
		token = token->next;
	}
	return (NULL);
}
