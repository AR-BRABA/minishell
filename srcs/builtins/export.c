/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:48:03 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 17:53:24 by jgils            ###   ########.fr       */
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

static int	handle_export_arg(char *arg, t_main *main)
{
	t_envnode	*new;
	t_envnode	*old;

	new = new_envnode(arg);
	if (!new)
		return (1);
	old = search_key(main->envp_list, new->key);
	if (!old && str_isname(new->key) && !ft_isdigit(new->key[0]))
		addback_env(new, main->envp_list);
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
	free_split(main->envp);
	main->envp = env_to_char_array(main->envp_list);
	return (0);
}

int	ft_export(char **args, t_main *main)
{
	int	ret;
	int	count;

	ret = 0;
	count = 0;
	while (args && args[count] != NULL)
	{
		if (handle_export_arg(args[count++], main))
			ret = 1;
	}
	return (ret);
}
