/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:04:39 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 16:04:40 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_main(t_main *main)
{
	rl_clear_history();
	free_split(main->envp);
	free_env(main->envp_list);
	if (main->cmdtab)
		free_table(main->cmdtab);
	free(main);
}

void	free_table(t_tab *cmdtable)
{
	t_list	*cmdline;
	t_list	*nextline;

	if (!cmdtable)
		return ;
	cmdline = cmdtable->head;
	while (cmdline != NULL)
	{
		nextline = cmdline->next;
		free_list(cmdline);
		cmdline = nextline;
	}
	free(cmdtable);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}