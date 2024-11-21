#include "../includes/minishell.h"

int	count_token_type(t_tab *cmdtab, int type)
{
	int	count = 0;
	t_list	*cmd = cmdtab->head;
	t_node	*token;

	while (cmd != NULL)
	{
		token = cmd->head;
		while (token != NULL)
		{
			if (token->type == type)
				count++;
			token = token->next;
		}
		cmd = cmd->next;
	}
	return count;
}

/*
char	**get_by_type(t_tab *cmdtab, int type)
{
	t_list	*cmd = cmdtab->head;
	t_node	*token = cmd->head;

	int	count = count_token_type(cmdtab, type);
	while (cmd != NULL && token != NULL)
	{
		if (token->type == type)
			count++;
		token = token->next;
		if (token->next == NULL)
		{
			cmd = cmd->next;
			if (cmd)
				token = cmd->head;
		}
	}
}

int	ft_pipe(t_tab *cmdtab, t_env *envp)
{
	int	i = 0;
	int	fd[2 * cmdtab->len];

	while (i < cmdtab->len * 2)
	{
		if (pipe(fd + (i * 2)) < 0)
			return 1;
		i++;
	}

	t_list *cmdline = cmdtab->head;
	t_node *token = cmdline->head;

	int pid;
	int cmd = 0;
	while (cmd != cmdtab->len)
	{
		pid = fork();
		if (pid < 0)
			return(1);
		if (pid == 0)
		{
			if (cmd != 0)
			{
				if (dup2(fd[(cmd - 1) * 2], 0) < 0)
					return 1;
			}
			if (cmd != cmdtab->len)
			{
				if (dup2(fd[(cmd + 1) * 2], 1) < 0)
					return 1;
			}
			cmd++;

			int	c = 0;
			while ( c <= cmdtab->len * 2)
				close(fd[c++]);

			// trocar para is_builtin para poder chamar perror caso nao seja builtin ou external command
			if (execute_builtins(token, envp, cmdtab) == -1)
				execute_external_command(token, envp->envp);
		}
		int	c = 0;
		while ( c <= cmdtab->len * 2)
			close(fd[c++]);
	}
	// closes all fds
	return 0;
}
*/
