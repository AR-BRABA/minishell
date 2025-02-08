/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:48:03 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 09:48:05 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(char *key, char *value, t_env *envp)
{
	t_envnode	*node;

	node = search_key(envp, key);
	free(node->value);
	node->value = ft_strdup(value);
}

void	update_envnode(char *value, t_envnode *node)
{
	free(node->value);
	node->value = ft_strdup(value);
}

static int	handle_export_arg(char *arg, t_env *envp)
{
	t_envnode	*new;
	t_envnode	*old;

	new = new_envnode(arg);
	if (!new)
		return (1);
	old = search_key(envp, new->key);
	if (!old && str_isname(new->key) && !ft_isdigit(new->key[0]))
		addback_env(new, envp);
	else
	{
		if (old)
			update_envnode(new->value, old);
		else
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			free_envnode(new);
			return (1);
		}
		free_envnode(new);
	}
	return (0);
}

int	ft_export(char **args, t_env *envp)
{
	int	ret;
	int	count;

	ret = 0;
	count = 0;
	while (args && args[count] != NULL)
	{
		if (handle_export_arg(args[count++], envp))
			ret = 1;
	}
	return (ret);
}
