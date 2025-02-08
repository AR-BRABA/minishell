/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:10:12 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 13:10:14 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_binary_path(char const *directory, char slash, char const *cmd)
{
	char	*bin_path;
	int		i;
	int		pos;

	if (!directory || !cmd)
		return (NULL);
	i = 0;
	pos = 0;
	bin_path = (char *)malloc(((ft_strlen(directory) + ft_strlen(cmd)) + 2)
			* sizeof(char));
	if (!bin_path)
		return (NULL);
	while (directory[i])
		bin_path[i++] = directory[pos++];
	bin_path[i++] = slash;
	pos = 0;
	while (cmd[pos])
		bin_path[i++] = cmd[pos++];
	bin_path[i] = '\0';
	return (bin_path);
}

char	*no_path(char **paths, char *absolute_path)
{
	free_split(paths);
	free(absolute_path);
	return (NULL);
}

char	*found_path(char **paths, char *absolute_path)
{
	free_split(paths);
	return (absolute_path);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*absolute_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		absolute_path = build_binary_path(paths[i++], '/', cmd);
		if (!absolute_path)
			return (no_path(paths, absolute_path));
		if (access(absolute_path, X_OK) == 0)
			return (found_path(paths, absolute_path));
		free(absolute_path);
	}
	free_split(paths);
	return (NULL);
}
