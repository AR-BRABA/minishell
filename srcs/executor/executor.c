/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 09:43:15 by tsoares-         ###   ########.fr       */
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

int	get_exit_status(t_main *main, int *pid)
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

void	try_exec(t_list *cmdlist, t_main *main)
{
	int	ret;

	if (cmdlist->fd[0] != 0)
	{
		if (dup2(cmdlist->fd[0], 0) < 0)
			return (perror("redirect"));
		close(cmdlist->fd[0]);
		cmdlist->fd[0] = 0;
	}
	if (cmdlist->fd[1] != 1)
	{
		if (dup2(cmdlist->fd[1], 1) < 0)
			return (perror("redirect"));
		close(cmdlist->fd[1]);
		cmdlist->fd[1] = 1;
	}
	if (cmdlist->fd[0] != 0)
		close(cmdlist->fd[0]);
	if (cmdlist->fd[1] != 1)
		close(cmdlist->fd[1]);
	ret = execute_builtins(cmdlist, main);
	if (ret == -1)
		execute_external_command(cmdlist, main);
	ft_exit_nbr(ret, main);
}

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

int	*init_execute_fork_commands(int *savefd, int *n, t_main *main)
{
	int	*pid;

	*n = -1;
	*savefd = -1;
	pid = malloc(sizeof(int) * main->cmdtab->len);
	return (pid);
}

int	freeturn(void *obj, int ret, int *fd, int *cmdfd)
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
	fprintf(stderr, "in: %i\nout: %i\n", cmdfd[0], cmdfd[1]);
	if (cmdfd[0] > 2)
		close(cmdfd[0]);
	if (cmdfd[1] > 2)
		close(cmdfd[1]);
	free(obj);
	return (ret);
}

int	execute_fork_commands(t_main *main)
{
	int		fd[2];
	int		savefd;
	t_list	*cmdlist;
	int		*pid;
	int		n;

	cmdlist = main->cmdtab->head;
	pid = init_execute_fork_commands(&savefd, &n, main);
	while (cmdlist != NULL)
	{
		if (cmdlist->next)
			if (pipe(fd) < 0)
				exit(1);
		if (pre_exec(cmdlist) == 1)
			return (freeturn(pid, 1, fd, cmdlist->fd));
		pid[++n] = fork();
		if (pid[n] < 0)
			return (freeturn(pid, 1, fd, cmdlist->fd));
		if (pid[n] == 0)
		{
			manipulate_fd(cmdlist, fd, &savefd, pid);
			try_exec(cmdlist, main);
		}
		parent(cmdlist, fd, &savefd);
		cmdlist = cmdlist->next;
	}
	return (get_exit_status(main, pid));
}

void	execute_commands(t_main *main)
{
	char	*exit;
	t_list	*cmdlist;

	cmdlist = main->cmdtab->head;
	if ((main->cmdtab->len == 1)
		&& (ft_strncmp(cmdlist->head->value, "cd", 3) == 0
			|| ft_strncmp(cmdlist->head->value, "export", 7) == 0
			|| ft_strncmp(cmdlist->head->value, "exit", 5) == 0
			|| ft_strncmp(cmdlist->head->value, "unset", 6) == 0))
	{
		main->fd[0] = dup(0);
		main->fd[1] = dup(1);
		redirect(cmdlist);
		exit = ft_itoa(execute_builtins(cmdlist, main));
		dup2(main->fd[0], 0);
		dup2(main->fd[1], 1);
		close(main->fd[0]);
		close(main->fd[1]);
	}
	else
		exit = ft_itoa(execute_fork_commands(main));
	if (g_tecno_status != -24)
		g_tecno_status = -24;
	update_env("?", exit, main->envp_list);
	free(exit);
}
