/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:18 by tsoares-          #+#    #+#             */
/*   Updated: 2024/11/22 21:06:18 by jgils            ###   ########.fr       */
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
	bin_path = (char *)malloc(((ft_strlen(directory)
				+ ft_strlen(cmd)) + 2) * sizeof(char));
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

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*absolute_path;
	int	i;

	i = 0;
	// procura a var path no envp
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);

	// remover "PATH=" p/ficar só c/os nomes dos diretórios
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');

	i = 0;
	while (paths[i])
	{
		absolute_path = build_binary_path(paths[i] + 5, '/', cmd);
		if (!absolute_path)
		{
			free_split(paths);
			free(absolute_path);
			return (NULL);
		}
		if (access(absolute_path, X_OK) == 0) // O comando pode ser executado?
		{
			free_split(paths);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	free_split(paths);
	return (NULL); // Se não achar o comando
}

static char **create_exec_args(t_node *token)
{
	char	**exec_args;
	int	count;
	t_node	*tmp_token;

	count = 1;
	tmp_token = token->next;
	while (tmp_token && tmp_token->type == ARG)
	{
		count++;
		tmp_token = tmp_token->next;
	}
	exec_args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!exec_args)
	{
		perror("allocation failure"); // criar macro p/padronizar msgs de erro
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

void execute_external_command(t_node *token, char **envp)
{
	pid_t	pid;
	char	**exec_args;  // Array para armazenar os argumentos
	char	*cmd_path;

	if (!token || !token->value)
	{
		ft_putstr_fd("Error: command not found: %s\n", 2);
		return ;
	}

	// buscar o caminho completo do comando
	cmd_path = find_command_path(token->value, envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Error: command not found in PATH\n", 2);
		return ;
	}

	exec_args = create_exec_args(token);
	if (!exec_args)
	{
		free(cmd_path);
        return ;
	}
	pid = fork();  // Criar processo filho p/ executar comando externo
	if (pid == 0)  // tô no processo filho
	{
		if (execve(cmd_path, exec_args, envp) == -1) // ver o errno
		{
			// salvar exit status no envp em $?
			perror("Error: execve failed");
			free(exec_args);
			free(cmd_path);
			exit(1);  // sair do processo filho
		}
	}
	else if (pid > 0)  // tô no processo pai
		wait(&pid);  // esperar qualquer processo filho terminar
	else
		perror("fork failed");
	free(exec_args);
	free(cmd_path);
}

// temp func:
void execute_external_pipe_command(t_node *token, char **envp)
{
	char	**exec_args;  // Array para armazenar os argumentos
	char	*cmd_path;

	if (!token || !token->value)
	{
		ft_putstr_fd("Error: command not found: %s\n", 2);
		return ;
	}

	// buscar o caminho completo do comando
	cmd_path = find_command_path(token->value, envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Error: command not found in PATH\n", 2);
		return ;
	}

	exec_args = create_exec_args(token);
	if (!exec_args)
	{
		free(cmd_path);
		return ;
	}
	if (execve(cmd_path, exec_args, envp) == -1) // ver o errno
	{
		// salvar exit status no envp em $?
		perror("Error: execve failed");
		free(exec_args);
		free(cmd_path);
		exit(1);  // sair do processo filho
	}
	free(exec_args);
	free(cmd_path);
}
