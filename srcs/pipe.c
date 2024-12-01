#include "../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	redirect(t_list *cmdline)
{
	int	fd[2];
	t_node *token= cmdline->head;

	// write(2, "entrou redirect\n", 4);
	while (token != NULL)
	{
		if (token->type == REDIRECT_IN)
		{
			fd[0] = open(token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0664);
			if (fd[0] < 0 || dup2(fd[0], 0) < 0)
				exit(1);
			close(fd[0]);
			token = token->next->next;
		}
		else if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			fd[1] = open(token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0664);
			if (fd[1] < 0 || dup2(fd[1], 1) < 0)
				exit(1);
			close(fd[1]);
			token = token->next->next;
		}
		else
			token = token->next;
	}
}

int	ft_pipe(t_tab *cmdtab, t_env *envp, char **env)
{
	int	fd[2];
	// int	std[2];
	int	save_fd[1];

	t_list *cmdline = cmdtab->head;

	int pid;
	int cmd = 0;
	while (cmdline != NULL)
	{
		if (cmdline->next)
			if (pipe(fd) < 0)
				exit(1);
		pid = fork();
		if (pid < 0)
			return(1);
		if (pid == 0)
		{
			if (cmdline->next)
			{
				if (dup2(fd[1], 1) < 0)
					exit(1);
			}
			if (cmdline->prev)
			{
				if (dup2(save_fd[0], 0) < 0)
					exit(1);
				close(save_fd[0]);
			}
			redirect(cmdline);
			close(fd[1]);
			close(fd[0]);
			int ret = execute_builtins(cmdline->head, envp, cmdtab);
			if (ret == -1)
				execute_external_pipe_command(cmdline, env);
			exit(ret);
		}
		save_fd[0] = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		cmd++;
		cmdline = cmdline->next;
	}
	int count = 0;
	int	status = 0;
	while (count < cmdtab->len)
		wait(&status);
	return 0;
}
