/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/20 15:57:57 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// test
t_node    *get_cmd(t_list *cmdlist)
{
    t_node  *token;

    token = cmdlist->head;
    while(token != NULL)
	{
		if (token->type == COMMAND)
			return (token);
		token = token->next;
	}
	return (NULL);
}

// tratar:
// erros
// leak? fds abertos
int	execute_fork_commands(t_main *main)
{
	int	fd[2];
	int	savefd = -1;
	t_list *cmdlist = main->cmdtab->head;
	int pid[main->cmdtab->len];
	int	n = -1;

	while (cmdlist != NULL)
	{
		// caso exista +1 comando(+ 1 cmdlist), cria 1 pipe com fd[2]
		if (cmdlist->next)
			if (pipe(fd) < 0)
				exit(1);
		// independente de quantos comandos, forka
		pid[++n] = fork();
		if (pid[n] < 0)
			return(1);
		if (pid[n] == 0)
		{
			// caso exista +1 comando, dup no fd out, que guardamos em fd[1]
			if (cmdlist->next)
			{
				if (dup2(fd[1], 1) < 0)
					exit(1);
				// fecha os fds que fizemos dup pois nao vamos mais nesse processo filho
				close(fd[0]);
				close(fd[1]);
			}
			// caso tenha 1 comando antes, dup no fd in do ->comando anterior,
			// que salvamos no fim do looping anterior
			if (cmdlist->prev)
			{
				if (dup2(savefd, 0) < 0)
					exit(1);
				close(savefd);
			}
			// faz todos os redirects desse comando (dessa command list)
			redirect(cmdlist);
			// tenta executar builtins, se nao conseguir, executa comando externo
			int ret = execute_builtins(cmdlist, main);
			if (ret == -1)
				execute_external_command(cmdlist, main->envp);
			// como estamos no processo filho, caso nao seja comando externo, precisamos encerrar o processo, assim como o execve
			exit(ret);
		}
		// fechando os fds no processo pai:
		// fechamos o fd in do comando anterior, caso esteja salvo (caso haja comando anterior)
		if (cmdlist->prev)
			close(savefd);
		// se ha um proximo comando, quer dizer que foi aberto um pipe nesse loop,
		if (cmdlist->next)
		{
			// entao temos que fechar o fd[1] e salvar o fd[0] pro prox comando
			close(fd[1]);
			savefd = fd[0];
		}
		cmdlist = cmdlist->next;
	}
	// exit status
	n = 0;
	int count = 0;
	int	status = 0;
	int	stat = 0;
	while (n < main->cmdtab->len)
	{
		waitpid(pid[n++], &status, 0);
		if (WIFEXITED(status))
			stat = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			stat = WTERMSIG(status);
		else if (WIFSTOPPED(status))
			stat = WSTOPSIG(status);
		count++;
	}
	// printf("!%i!\n", stat);
	return stat;
}

void	execute_commands(t_main *main)
{
	char *exit;
	t_list	*cmdlist;

	cmdlist = main->cmdtab->head;
	// exception: simple commands that should be executed on main process (cd, export, unset)
	if ((main->cmdtab->len == 1) && 
			(ft_strncmp(cmdlist->head->value, "cd", 3) == 0 ||
			ft_strncmp(cmdlist->head->value, "export", 7) == 0 ||
			ft_strncmp(cmdlist->head->value, "exit", 5) == 0 ||
			ft_strncmp(cmdlist->head->value, "unset", 6) == 0))
	{

		// TODO: check success on dups and fix open fds!!!

		// save std in/out fds
		int savefd[2];
		savefd[0] = dup(0);
		savefd[1] = dup(1);

		// redirect fd in/out
		redirect(cmdlist);

		// execute
		exit = ft_itoa(execute_builtins(cmdlist, main));
		
		// restore std in/out fd;
		dup2(savefd[0], 0);
		dup2(savefd[1], 1);

		// close dup fds
		close(savefd[0]);
		close(savefd[1]);
	}
	else
		exit = ft_itoa(execute_fork_commands(main));
	update_env("?", exit, main->envp_list);
	free(exit);
}

/*
void	execute_commands(t_tab *cmdtable, t_env *env, char **envp)
{
	t_list	*cmdlist;
	t_node	*token;

	cmdlist = cmdtable->head;
	while (cmdlist != NULL)
	{
		token = cmdlist->head; // 1º token do user_input é o comando
		if (token != NULL) // DEBUG para saber se o token que tá chegando é inválido
		{
			int i = 0;
			t_node *tmp_token = token;
			while (tmp_token != NULL)
        		{
            			//printf("executor.c --> Token %d: %s\n", i, tmp_token->value);
            			i++;
            			tmp_token = tmp_token->next;
        		}
			if (execute_builtins(token, env, cmdtable) == -1) // trocar para is_builtin para poder chamar perror caso nao seja builtin ou external command
				execute_external_command(cmdlist, envp);
			//else
				//perror("Error: Invalid command");
		}
		else
			printf("executor.c --> comando inválido | token é NULL\n"); // DEBUG
		cmdlist = cmdlist->next;
	}
}
*/
