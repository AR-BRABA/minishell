/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2024/11/09 21:58:20 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtins(t_node *token, t_env *env, t_tab *cmdtab)
{
	int	i;
	char	**args;

	args = NULL;
	if (!token || !token->value)
		return (0);
	if (ft_strncmp(token->value, "cd", 3) == 0)
	{
		if (token->next)
			args = list_to_char_array(token->next);
		i = cd(args, env);
		if (args)
			free(args);
		return(i);
	}
	else if (ft_strncmp(token->value, "echo", 5) == 0)
	{
		if (!token->next)
			return (echo(NULL));
		args = list_to_char_array(token->next);
		if (!args)
			return (0);
		i = echo(args); // chamar echo c/o array de argumentos
		free(args);
		return (i);
	}
	else if (ft_strncmp(token->value, "exit", 5) == 0)
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // se não tiver argumento chama exit sem argumento????
		return (miniexit(args, env, cmdtab)); // exit encerra o programa
	}
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		return (pwd());
	else if (ft_strncmp(token->value, "env", 4) == 0)
		return (minienv(env));
	else if (ft_strncmp(token->value, "unset", 6) == 0) // implement unset
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // Qual erro retornar se não tiver argumentos mesmo?
		i = unset(args, env);
		free(args);
		return(i);
	}
	else if (ft_strncmp(token->value, "export", 7) == 0) // implement unset
	{
		args = list_to_char_array(token->next);
		if (!args)
			return (0); // Qual erro retornar se não tiver argumentos mesmo?
		i = export(args, env);
		free(args);
		return(i);
	}
	return (-1); // Se não for built-in, retornar -1
}
