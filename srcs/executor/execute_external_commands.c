/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:18 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 15:14:24 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*merror(char *msg, void *ret)
{
	perror(msg);
	return (ret);
}

char	**init_exec_args(t_node *token)
{
	char	**exec_args;
	int		count;
	t_node	*tmp_token;

	count = 1;
	tmp_token = token->next;
	while (tmp_token && tmp_token->type == ARG)
	{
		count++;
		tmp_token = tmp_token->next;
	}
	exec_args = (char **)malloc(sizeof(char *) * (count + 1));
	return (exec_args);
}

static char	**create_exec_args(t_node *token)
{
	char	**exec_args;
	int		count;
	t_node	*tmp_token;

	exec_args = init_exec_args(token);
	if (!exec_args)
		return (merror("malloc:", NULL));
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

void	execve_error(t_node *token, t_main *main, char **exec_args,
		char *cmd_path)
{
	perror(token->value);
	free_main(main);
	free(exec_args);
	free(cmd_path);
	exit(127);
}

void	execute_external_command(t_list *cmdlist, t_main *main)
{
	char	**exec_args;
	char	*cmd_path;
	t_node	*token;

	token = get_cmd(cmdlist);
	if (!token || !token->value)
		return (perror(token->value));
	if (access(token->value, X_OK) == 0)
		cmd_path = ft_strdup(token->value);
	else
		cmd_path = find_command_path(token->value, main->envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		free(cmd_path);
		free_main(main);
		exit(127);
	}
	exec_args = create_exec_args(token);
	if (!exec_args)
		free(cmd_path);
	if (execve(cmd_path, exec_args, main->envp) == -1)
		execve_error(token, main, exec_args, cmd_path);
}
