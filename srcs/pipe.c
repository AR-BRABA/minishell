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

char	**get_value_by_type(t_tab *cmdtab, int type)
{
	t_list	*cmd = cmdtab->head;
	t_node	*token = cmd->head;

	int	count = count_token_type(cmdtab, type);
	char **array = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (cmd != NULL)
	{
		token = cmd->head;
		while (token != NULL)
		{
			if (token->type == type)
				array[count++] = ft_strdup(token->value);
			token = token->next;
		}
		cmd = cmd->next;
	}
	return (array);
}

// t_node	*get_next_token(t_tab *cmdtab, t_node *start, int type)
// {
// 	t_list	*cmd = cmdtab->head;
// 	t_node	*token = start;
//
// 	while (cmd != NULL)
// 	{
// 		if (!token)
// 			token = cmd->head;
// 		while (token != NULL)
// 		{
// 			if (token->type == type)
// 				return (token);
// 			token = token->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (NULL);
// }

int	ft_pipe(t_tab *cmdtab, t_env *envp, char **env)
{
	int	i = 0;
	int	fd[2 * cmdtab->len];

	while (i < cmdtab->len)
	{
		if (pipe(fd + (i * 2)) < 0)
			exit(1);
		i++;
	}

	t_list *cmdline = cmdtab->head;

	int pid;
	int cmd = 0;
	while (cmdline != NULL)
	{
		pid = fork();
		if (pid < 0)
			return(1);
		if (pid == 0)
		{
			//fd in
			if (cmd > 0) // se n for o primeiro
			{
				if (dup2(fd[(cmd - 1) * 2], 0) < 0)
					exit(1);
			}
			// fd out
			if (cmd < cmdtab->len - 1) //se n for o ultimo
			{
				if (dup2(fd[cmd * 2 + 1], 1) < 0)
					exit(1);
			}

			int	c = 0;
			while ( c < (cmdtab->len * 2))
				close(fd[c++]);

			// temporariamente executando por aqui (integrar com execucao no futuro)
			if (execute_builtins(cmdline->head, envp, cmdtab) == -1)
				execute_external_pipe_command(cmdline->head, env);

		}
		// printf("SAIUUUUUU %i\n", pid);
		cmd++;
		cmdline = cmdline->next;
	}
	int	c = 0;
	while ( c < (cmdtab->len * 2))
		close(fd[c++]);
	if (pid != 0)
		wait(&pid);
	return 0;
}
