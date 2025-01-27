/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/27 15:23:29 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%d: <%s>\n", i, array[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	t_node	*node;

	node = list->head;
	if (!node)
	{
		printf("no list!!\n\n");
		return ;
	}
	node = list->head;
	while (node != NULL)
	{
		printf("{value = !%s! \\ type = %i}->", node->value, node->type);
		node = node->next;
	}
	printf("NULL\n");
}

int	execute_builtins(t_list *cmdlist, t_main *main)
{
	char	**args;
	t_node	*token;

	token = get_cmd(cmdlist);
	args = NULL;
	if (token->next)
		args = list_to_char_array(token->next);
	if (ft_strncmp(token->value, "cd", 3) == 0)
		return (ft_cd(args, main->envp_list));
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(token->value, "env", 4) == 0)
		return (ft_env(args, main->envp_list));
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		return (ft_exit(args, main));
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		return (ft_echo(args));
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		return (ft_unset(args, main->envp_list));
	else if (ft_strncmp(token->value, "export", 7) == 0)
		return (ft_export(args, main->envp_list));
	if (token->next && args)
		free(args);
	return (-1);
}
