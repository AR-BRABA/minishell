/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:10:26 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 16:14:41 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pc_get_exit_status(t_main *main, int *pid)
{
	int	status;
	int	stat;
	int	n;

	n = 0;
	status = 0;
	stat = 0;
	while (n < main->cmdtab->len)
	{
		waitpid(pid[n++], &status, 0);
		if (WIFEXITED(status))
			stat = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			stat = WTERMSIG(status) + 128;
		else if (WIFSTOPPED(status))
			stat = WSTOPSIG(status);
	}
	free(pid);
	return (stat);
}

int	*init_execute_fork_commands(int *savefd, int *fd, int *n, t_main *main)
{
	int	*pid;

	fd[0] = 0;
	fd[1] = 1;
	*n = -1;
	*savefd = -1;
	pid = malloc(sizeof(int) * main->cmdtab->len);
	return (pid);
}

int	freeturn(void *pid, int ret, int *fd, int *cmdfd)
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
	if (cmdfd[0] > 2)
		close(cmdfd[0]);
	if (cmdfd[1] > 2)
		close(cmdfd[1]);
	free(pid);
	return (ret);
}
