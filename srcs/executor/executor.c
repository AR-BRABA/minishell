/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:28 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/02 16:17:09 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_commands(t_tab *cmdtable)
{
	t_list	*cmdlist;
	t_node	*token;

	cmdlist = cmdtable->head;
	// token = NULL;
	while (cmdlist != NULL)
	{
		token = cmdlist->head; // 1º token do user_input é o comando
		execute_external_command(token);
		/*if (!execute_builtins(token))
		{
			printf("CHAMANDO EXECUTE_EXTERNAL_COMMANDS");
			execute_external_command(token);
		}	*/	
		// Se tiver mais linhas de comando, ir p/a próxima
		cmdlist = cmdlist->next;
	}
}
