/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:18 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/16 19:37:53 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

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

	// cria o caminho completo pra cada diretório no PATH
	i = 0;
	while (paths[i])
	{
		absolute_path = (char *)malloc(sizeof(char) * ft_strlen(paths[i] + ft_strlen(cmd) + 2));
		if (!absolute_path)
			return (NULL);
		ft_strlcpy(absolute_path, paths[i], ft_strlen(paths[i]) + 1); // Copiar o diretório
		ft_strlcat(absolute_path, "/", ft_strlen(absolute_path) + 2); // adiciona a /
		ft_strlcat(absolute_path, cmd, ft_strlen(absolute_path) + ft_strlen(cmd) + 1); // add o comando
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

	count = 0;
	tmp_token = token;
	while (tmp_token)
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
	while (token)
	{
		exec_args[count++] = token->value;
		token = token->next;
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
		if (execve(cmd_path, exec_args, envp) == -1)
		{
			perror("Error: execve failed");
			free(exec_args);
			free(cmd_path);
			exit(1);  // sair do processo filho
		}
	}
    	else if (pid > 0)  // tô no processo pai
        	wait(NULL);  // esperar processo filho terminar
    	else
        	perror("fork failed");
    	free(exec_args);
		free(cmd_path);

    // DEBUG --> preenche exec_args com os tokens do comando e argumentos
//    while (token != NULL)
//    {
//        exec_args[i++] = token->value;
//        token = token->next;
//    }
//    exec_args[i] = NULL;  // args deve terminar com NULL para execve

    // DEBUG
//    printf("execve vai executar o comando: %s\n", exec_args[0]);

//    pid = fork();  // Criar processo filho p/ executar comando externo
//    if (pid == 0)  // tô no processo filho
//    {
        /* // formatar os tokens em um array de argumentos
        arg_token = token;
        while (arg_token != NULL)
        {
            exec_args[i] = arg_token->value;  // preencher cada argumento
            arg_token = arg_token->next;
            i++;
        }
        exec_args[i] = NULL;*/

        // executar comando externo com execvp
//	if (execve(exec_args[0], exec_args, NULL) == -1)
//	{
//            perror("execve failed");
//            exit(1);  // sair do processo filho
//        }
//    }
//    else if (pid > 0)  // tô no processo pai
//        wait(NULL);  // esperar processo filho terminar
//    else
//        perror("fork failed");
}
