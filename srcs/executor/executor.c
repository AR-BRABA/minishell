/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/01 18:13:55 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_commands(t_tab *cmdtable, t_env *env, char **envp)
{
	t_list	*cmdlist;

	cmdlist = cmdtable->head;
	if (cmdtable->len == 1)
	{
			int ret = execute_builtins(cmdlist->head, env, cmdtable);
			if (ret == -1)
			{
				int pid = fork();
				if (pid == 0)
					execute_external_pipe_command(cmdlist, envp);
				else
					wait(&pid);
			}
			// else	
				//exit status
	}
	else
		ft_pipe(cmdtable, env, envp);
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
