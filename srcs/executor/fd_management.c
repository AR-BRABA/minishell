#include "../../includes/minishell.h"

void	manipulate_fd(t_list *cmdlist, int *fd, int *savefd, int *pid)
{
	free(pid);
	if (cmdlist->next)
	{
		if (dup2(fd[1], 1) < 0)
			exit(1);
		close(fd[0]);
		close(fd[1]);
	}
	if (cmdlist->prev)
	{
		if (dup2(*savefd, 0) < 0)
			exit(1);
		close(*savefd);
	}
}

void	parent(t_list *cmdlist, int *fd, int *savefd)
{
	if (cmdlist->fd[0] != 0)
		close(cmdlist->fd[0]);
	if (cmdlist->fd[1] != 1)
		close(cmdlist->fd[1]);
	if (cmdlist->prev)
		close(*savefd);
	if (cmdlist->next)
	{
		close(fd[1]);
		*savefd = fd[0];
	}
}