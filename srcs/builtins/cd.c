/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:48:16 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 09:48:18 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key_value(t_env *list, char *key)
{
	char		*val;
	t_envnode	*node;

	node = search_key(list, key);
	if (node)
		val = ft_strdup(node->value);
	else
		val = NULL;
	return (val);
}

void	update_key_value(t_env *list, char *key, char *new_val)
{
	t_envnode	*node;

	node = search_key(list, key);
	if (node && node->value)
	{
		free(node->value);
		node->value = ft_strdup(new_val);
	}
}

char	*get_path(char **args, t_env *env)
{
	char	*path;

	path = NULL;
	if (!args || (args && ft_strncmp(args[0], "~", 1) == 0))
	{
		path = get_key_value(env, "HOME");
		if (args && args[0][1] != '\0')
			path = ft_strfjoin(path, &args[0][1]);
	}
	else if (args && ft_strncmp(args[0], "-", 2) == 0)
		path = get_key_value(env, "OLDPWD");
	else if (args)
		path = ft_strdup(args[0]);
	return (path);
}

int	ft_cd(char **args, t_env *env)
{
	char	*origin;
	char	*path;
	char	buf[PATH_MAX + 1];

	if (split_len(args) > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 2);
	path = get_path(args, env);
	origin = getcwd(buf, PATH_MAX + 1);
	if (chdir(path) == -1 || !origin)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		free(path);
		return (1);
	}
	update_key_value(env, "OLDPWD", origin);
	update_key_value(env, "PWD", path);
	free(path);
	return (0);
}
