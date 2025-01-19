/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 16:04:56 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*get_cmd(t_list *cmdlist)
{
	t_node	*token;

	token = cmdlist->head;
	while (token != NULL)
	{
		if (token->type == COMMAND)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	execute_fork_commands(t_main *main)
{
	int		fd[2];
	int		savefd;
	t_list	*cmdlist;
	int		pid[main->cmdtab->len];
	int		n;
	int		count;
	int		status;
	int		ret;

	savefd = -1;
	cmdlist = main->cmdtab->head;
	n = -1;
	while (cmdlist != NULL)
	{
		// caso exista +1 comando(+ 1 cmdlist), cria 1 pipe com fd[2]
		if (cmdlist->next)
			if (pipe(fd) < 0)
				exit(1);
		// independente de quantos comandos, forka
		pid[++n] = fork();
		if (pid[n] < 0)
			return (1);
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
			ret = redirect(cmdlist);
			if (ret == 0)
			{
				ret = execute_builtins(cmdlist, main);
				if (ret == -1)
					execute_external_command(cmdlist, main->envp);
				// como estamos no processo filho,
				//		caso nao seja comando externo,
				// precisamos encerrar o processo, assim como o execve
				exit(ret);
			}
		}
		// fechando os fds no processo pai:
		// fechamos o fd in do comando anterior,
		//	caso esteja salvo (caso haja comando anterior)
		if (cmdlist->prev)
			close(savefd);
		// se ha um proximo comando,
		//	quer dizer que foi aberto um pipe nesse loop,
		if (cmdlist->next)
		{
			// entao temos que fechar o fd[1] e salvar o fd[0] pro prox comando
			close(fd[1]);
			savefd = fd[0];
		}
		cmdlist = cmdlist->next;
	}
	n = 0;
	count = 0;
	status = 0;
	ret = 0;
	while (n < main->cmdtab->len)
	{
		waitpid(pid[n++], &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ret = WTERMSIG(status);
		else if (WIFSTOPPED(status))
			ret = WSTOPSIG(status);
		count++;
	}
	return (ret);
}

void	execute_commands(t_main *main)
{
	int		ret;
	char	*status;
	t_list	*cmdlist;

	cmdlist = main->cmdtab->head;
	if ((main->cmdtab->len == 1) &&
		(ft_strncmp(cmdlist->head->value, "cd", 3) == 0 ||
			ft_strncmp(cmdlist->head->value, "export", 7) == 0 ||
			ft_strncmp(cmdlist->head->value, "exit", 5) == 0 ||
			ft_strncmp(cmdlist->head->value, "unset", 6) == 0))
	{
		main->fd[0] = dup(0);
		main->fd[1] = dup(1);
		ret = redirect(cmdlist);
		if (ret == 0)
			status = ft_itoa(execute_builtins(cmdlist, main));
		dup2(main->fd[0], 0);
		dup2(main->fd[1], 1);
		close(main->fd[0]);
		close(main->fd[1]);
	}
	else
		status = ft_itoa(execute_fork_commands(main));
	update_env("?", status, main->envp_list);
	free(status);
}
