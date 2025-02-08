/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 18:00:51 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_node *token, char **args, t_main *main)
{
	if (ft_strncmp(token->value, "cd", 3) == 0)
		return (ft_cd(args, main));
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		return (ft_echo(args));
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		return (ft_exit(args, main));
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(token->value, "env", 4) == 0)
		return (ft_env(main->envp_list));
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		return (ft_unset(args, main));
	else if (ft_strncmp(token->value, "export", 7) == 0)
		return (ft_export(args, main));
	return (-1);
}

int	execute_builtins(t_list *cmdlist, t_main *main)
{
	int		i;
	char	**args;
	t_node	*token;

	i = -1;
	token = get_cmd(cmdlist);
	args = NULL;
	if (!token || !token->value)
		return (0);
	if (token->next)
		args = list_to_char_array(token->next);
	i = exec_cmd(token, args, main);
	free_split(args);
	return (i);
}
