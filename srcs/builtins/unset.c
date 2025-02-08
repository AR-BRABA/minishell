/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:48:47 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 17:51:02 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **args, t_main *main)
{
	int			count;
	t_envnode	*node;

	count = 0;
	while (args && args[count] != NULL)
	{
		node = search_key(main->envp_list, args[count]);
		if (!node)
			return (0);
		if (node->next)
			node->next->prev = node->prev;
		if (node->prev)
			node->prev->next = node->next;
		free(node->key);
		free(node->value);
		free(node);
		free_split(main->envp);
		main->envp = env_to_char_array(main->envp_list);
		count++;
	}
	return (0);
}
