/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 00:09:43 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	try_exec(t_list *cmdlist, t_main *main)
{
	int	ret;

	if (cmdlist->fd[0] > 2)
	{
		if (dup2(cmdlist->fd[0], 0) < 0)
			return (perror("redirect"));
		close(cmdlist->fd[0]);
		cmdlist->fd[0] = 0;
	}
	if (cmdlist->fd[1] > 2)
	{
		if (dup2(cmdlist->fd[1], 1) < 0)
			return (perror("redirect"));
		close(cmdlist->fd[1]);
		cmdlist->fd[1] = 1;
	}
	if (cmdlist->fd[0] > 2)
		close(cmdlist->fd[0]);
	if (cmdlist->fd[1] > 2)
		close(cmdlist->fd[1]);
	ret = execute_builtins(cmdlist, main);
	if (ret == -1)
		execute_external_command(cmdlist, main);
	ft_exit_nbr(ret, main);
}

void	decide_pipe(t_main *main, t_list *cmdlist)
{
	if (cmdlist->next)
		if (pipe(main->fd) < 0)
			ft_exit_nbr(1, main);
}

int	execute_fork_commands(t_main *main)
{
	int		savefd;
	t_list	*cmdlist;
	int		*pid;
	int		n;

	cmdlist = main->cmdtab->head;
	pid = init_execute_fork_commands(&savefd, &n, main);
	while (cmdlist != NULL)
	{
		decide_pipe(main, cmdlist);
		if (pre_exec(cmdlist) == 1)
			return (freeturn(pid, 1, main->fd, cmdlist->fd));
		pid[++n] = fork();
		if (pid[n] < 0)
			return (freeturn(pid, 1, main->fd, cmdlist->fd));
		if (pid[n] == 0)
		{
			manipulate_fd(cmdlist, main->fd, &savefd, pid);
			try_exec(cmdlist, main);
		}
		parent(cmdlist, main->fd, &savefd);
		cmdlist = cmdlist->next;
	}
	return (pc_get_exit_status(main, pid));
}

void	restore_fd(int *fd, char *exit, t_main *main)
{
	if (dup2(fd[0], 0) < 0)
	{
		perror("redirect");
		if (g_tecno_status != -24)
			ft_exit(&exit, main);
		free(exit);
		ft_exit_nbr(g_tecno_status, main);
	}
	if (dup2(fd[1], 1) < 0)
	{
		perror("redirect");
		if (g_tecno_status == -24)
			ft_exit_nbr(g_tecno_status, main);
		ft_exit(&exit, main);
	}
	close(fd[0]);
	close(fd[1]);
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
		restore_fd(main->fd, exit, main);
	}
	else
		exit = ft_itoa(execute_fork_commands(main));
	if (g_tecno_status != -24)
		g_tecno_status = -24;
	fprintf(stderr, "tecno: %i\n", g_tecno_status);
	fprintf(stderr, "exit: %s\n", exit);
	update_env("?", exit, main->envp_list);
	free(exit);
}
