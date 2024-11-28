#include "../includes/minishell.h"

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
			close(fd[1]);
			close(fd[0]);
			if (execute_builtins(cmdline->head, envp, cmdtab) == -1)
				execute_external_pipe_command(cmdline->head, env);

		}
		else
			wait(&pid);
		save_fd[0] = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		cmd++;
		cmdline = cmdline->next;
	}
	return 0;
}
