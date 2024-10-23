/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/16 17:46:37 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtins(t_node *token, t_env *env)
{
	int	i;
	int	count;
	char	**args;
	t_node	*arg_token;

	if (!token || !token->value)
		return (0);
	if (ft_strncmp(token->value, "cd", 2) == 0)
	{
		if (token->next)
			return (cd(token->next->value, env));
		return (cd(NULL, env));
    }
    else if (ft_strncmp(token->value, "echo", 4) == 0)
	{
		if (!token->next)
			return (echo(NULL));
		arg_token = token->next;
		count = 0;
		while (arg_token) // contar o nº de argumentos
		{
			count++;
			arg_token = arg_token->next;
		}
		args = (char **)malloc(sizeof(char *) * (count + 1)); // criar um array de strings para passar para o echo
		if (!args)
		{
			perror("Error: memory allocation failure!\n");
			return (0);
		}
		arg_token = token->next; // voltar p/o 1º argumento e depois copiar os args p/o array
		i = 0;
		while (arg_token) // preencher o array de argumentos;
		{
			if (!arg_token->value)
			{
				free(args); // se der erro, dar free
				return (0);
			}
			args[i] = arg_token->value; // copiar o valor do token p/o array de args
			i++;
			arg_token = arg_token->next;
		}
		args[i] = NULL;
		i = echo(args); // chamar echo c/o array de argumentos
		free(args);
		return (i);
	}
   	/*else if (ft_strncmp(token->value, "exit", 4) == 0)
    {
        builtin_exit();
        return (1);
    }*/
    else if (ft_strncmp(token->value, "pwd", 3) == 0)
		return (pwd());
	return (-1); // Se não for built-in, retornar -1
}