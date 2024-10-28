/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/22 15:06:03 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_commands(t_tab *cmdtable, t_env *env)
{
	t_list	*cmdlist;
	t_node	*token;

	cmdlist = cmdtable->head;
	while (cmdlist != NULL)
	{
		token = cmdlist->head; // 1º token do user_input é o comando
		/*if (token != NULL) // DEBUG para saber se o token que tá chegando é inválido
		{
			int i = 0;
			t_node *tmp_token = token;
			while (tmp_token != NULL)
        		{
            			//printf("executor.c --> Token %d: %s\n", i, tmp_token->value);
            			i++;
            			tmp_token = tmp_token->next;
        		}*/
			if (execute_builtins(token, env, cmdtable) == -1) // trocar para is_builtin para poder chamar perror caso nao seja builtin ou external command
				execute_external_command(token, env->envp);
			//else
				//perror("Error: Invalid command");
		/*}
		else
			printf("executor.c --> comando inválido | token é NULL\n"); // DEBUG*/
		cmdlist = cmdlist->next;
	}
}
