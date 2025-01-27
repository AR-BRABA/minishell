/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/27 18:11:21 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtins(t_list *cmdlist, t_main *main)
{
	int		ret;
	char	**args;
	t_node	*token;

	ret = -1;
	token = get_cmd(cmdlist);
	args = list_to_char_array(token->next);
	if (ft_strncmp(token->value, "cd", 3) == 0)
		ret = ft_cd(args, main->envp_list);
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(token->value, "env", 4) == 0)
		ret = ft_env(args, main->envp_list);
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		ret = ft_exit(args, main);
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		ret = ft_echo(args);
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		ret = ft_unset(args, main->envp_list);
	else if (ft_strncmp(token->value, "export", 7) == 0)
		ret = ft_export(args, main->envp_list);
	if (args)
		free_split(args);
	return (ret);
}
