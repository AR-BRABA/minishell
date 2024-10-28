/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:12:01 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/25 15:29:32 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 ** Converts the token linked list into a array of strings (char **) 
 */

char    **list_to_char_array(t_node *token)
{
    int     count;
    int     i;
    char    **args;
    t_node  *arg_token;

    count = 0;
    i = 0;
    arg_token = token;
    while(arg_token)
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
	arg_token = token; // voltar p/o 1º argumento e depois copiar os args p/o array
	i = 0;
	while (arg_token) // preencher o array de argumentos;
	{
		if (!arg_token->value)
		{
			free(args); // se der erro, dar free
			return (0);
		}
		args[i++] = arg_token->value; // copiar o valor do token p/o array de args
		arg_token = arg_token->next;
	}
	args[i] = NULL;
    return (args);
}