/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:03:32 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 14:03:44 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* search key on env list. returna an env node with key and value,
	if found. else: NULL. free key*/
t_envnode	*search_key(t_env *list, char *key)
{
	int			keylen;
	t_envnode	*env;

	keylen = ft_strlen(key);
	env = list->head;
	while (env != NULL)
	{
		if (ft_strncmp(key, env->key, keylen + 1) == 0)
			break ;
		env = env->next;
	}
	return (env);
}

char	*get_variable_value(t_env *env, char *var, int varlen)
{
	char		*hold;
	t_envnode	*node;

	hold = strndup(var + 1, varlen - 1);
	node = search_key(env, hold);
	free(hold);
	if (node)
		return (node->value);
	return (NULL);
}
