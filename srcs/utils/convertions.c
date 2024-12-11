/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:12:01 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/10 23:59:57 by jgils            ###   ########.fr       */
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
    while(arg_token && arg_token->type == ARG)
	{
		count++;
		arg_token = arg_token->next;
	}
	args = (char **)malloc(sizeof(char *) * (count + 1)); // criar um array de strings para passar para o ft_echo
	if (!args)
	{
		perror("Error: memory allocation failure!\n");
		return (0);
	}
	arg_token = token; // voltar p/o 1º argumento e depois copiar os args p/o array
	i = 0;
	while (arg_token && arg_token->type == ARG) // preencher o array de argumentos;
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

// test
char    **get_args_array(t_list *cmdlist)
{
    int     count;
    int     i;
    char    **args;
    t_node  *token;

    count = 0;
    token = cmdlist->head;
    while(token)
    {
	    if(token->type == ARG)
		    count++;
	    token = token->next;
    }
    args = (char **)malloc(sizeof(char *) * (count + 1)); // criar um array de strings para passar para o ft_echo
    if (!args)
    {
	    perror("Error: memory allocation failure!\n");
	    return (0);
    }
    token = cmdlist->head; // voltar p/o 1º argumento e depois copiar os args p/o array
    i = 0;
    while(token)
    {
	    if(token->type == ARG)
	    {
		    args[i++] = ft_strdup(token->value); // copiar o valor do token p/o array de args
	    }
	    token = token->next;
    }
    args[i] = NULL;
    return (args);
}

// test
char	**env_to_char_array(t_env *envp)
{
	int	count = 0;
	t_envnode	*node;
	char **array;
	
	if (!envp || !envp->head)
		return (NULL);
	array = malloc((envp->len + 1) * sizeof (char *));
	node = envp->head;
	while (node != NULL)
	{
		if (node->key[0] != '?')
		{
			array[count] = ft_strjoin("", node->key);
			array[count] = ft_strjoin(array[count], "=");
			array[count] = ft_strjoin(array[count], node->value);
			count++;
		}
		node = node->next;
	}
	array[count] = NULL;
	return (array);
}
