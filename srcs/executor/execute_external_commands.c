/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:18 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/21 21:06:13 by jgils            ###   ########.fr       */
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

char	**get_paths(char **envp)
{
	char	*path_env;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*absolute_path;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		absolute_path = build_binary_path(paths[i++], '/', cmd);
		if (!absolute_path)
		{
			free_split(paths);
			free(absolute_path);
			return (NULL);
		}
		if (access(absolute_path, X_OK) == 0)
		{
			free_split(paths);
			return (absolute_path);
		}
		free(absolute_path);
	}
	free_split(paths);
	return (NULL);
}

static char	**create_exec_args(t_node *token)
{
	char	**exec_args;
	int		count;
	t_node	*tmp_token;

	count = 1;
	tmp_token = token->next;
	while (tmp_token && tmp_token->type == ARG && count++)
		tmp_token = tmp_token->next;
	exec_args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!exec_args)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	count = 0;
	tmp_token = token;
	exec_args[count++] = tmp_token->value;
	tmp_token = tmp_token->next;
	while (tmp_token && tmp_token->type == ARG)
	{
		exec_args[count++] = tmp_token->value;
		tmp_token = tmp_token->next;
	}
	exec_args[count] = NULL;
	return (exec_args);
}

void	execute_external_command(t_list *cmdlist, t_main *main)
{
	char	*cmd_path;
	t_node	*token;
	char	**exec_args;

	token = get_cmd(cmdlist);
	if (!token || !token->value)
		return (perror(token->value));
	if (access(token->value, X_OK) == 0)
		cmd_path = ft_strdup(token->value);
	else
		cmd_path = find_command_path(token->value, main->envp);
	exec_args = create_exec_args(token);
	if (!exec_args)
		return (free(cmd_path));
	if (!cmd_path || execve(cmd_path, exec_args, main->envp) == -1)
	{
		if (!cmd_path)
			ft_putstr_fd("minishell: command not found\n", 2);
		else
			perror(token->value);
		free(exec_args);
		free(cmd_path);
		free_main(main);
		exit(127);
	}
}
