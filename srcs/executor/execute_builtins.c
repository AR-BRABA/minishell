/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/10 19:08:20 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtins(t_list *cmdlist, t_main *main)
{
	int	i;
	char	**args;
	t_node *token = get_cmd(cmdlist);

	args = NULL;
	if (!token || !token->value)
		return (0);
	if (ft_strncmp(token->value, "cd", 3) == 0)
	{
		if (token->next)
			args = list_to_char_array(token->next);
		i = ft_cd(args, main->envp_list);
		if (args)
			free(args);
		return(i);
	}
	else if (ft_strncmp(token->value, "echo", 5) == 0)
	{
		if (!token->next)
			return (ft_echo(NULL));
		args = list_to_char_array(token->next);
		if (!args)
			return (0);
		i = ft_echo(args); // chamar ft_echo c/o array de argumentos
		free(args);
		return (i);
	}
	else if (ft_strncmp(token->value, "exit", 5) == 0)
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // se não tiver argumento chama exit sem argumento????
		return (ft_exit(args, main)); // exit encerra o programa
	}
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(token->value, "env", 4) == 0)
		return (ft_env(main->envp_list));
	else if (ft_strncmp(token->value, "unset", 6) == 0) // implement ft_unset
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // Qual erro retornar se não tiver argumentos mesmo?
		i = ft_unset(args, main->envp_list);
		free(args);
		return(i);
	}
	else if (ft_strncmp(token->value, "export", 7) == 0) // implement ft_unset
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // Qual erro retornar se não tiver argumentos mesmo?
		i = ft_export(args, main->envp_list);
		free(args);
		return(i);
	}
	return (-1); // Se não for built-in, retornar -1
}
