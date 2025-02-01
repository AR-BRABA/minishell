/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:12:01 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/15 23:55:10 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 ** Converts the token linked list into a array of strings (char **) 
 */

char **get_args(t_node *token)
{
    int     count;
    char    **args;
    t_node  *arg_token;

    count = 0;
    arg_token = token;
    while(arg_token && arg_token->type == ARG)
	{
		if (arg_token->type == ARG)
			count++;
		arg_token = arg_token->next;
	}
	if (!count)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("Error: memory allocation failure!\n");
		return (NULL);
	}
	return (args);
}

char    **list_to_char_array(t_node *token)
{
	char **args;
    t_node  *arg_token;
	int	i;

	i = 0;
	args = get_args(token);
	arg_token = token;
	if (!args)
		return (NULL);
	while (arg_token)
	{
		if (!arg_token->value)
		{
			free(args);
			return (0);
		}
		if (arg_token->type == ARG)
			args[i++] = ft_strdup(arg_token->value);
		arg_token = arg_token->next;
	}
	args[i] = NULL;
    return (args);
}

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
		args = (char **)malloc(sizeof(char *) * (count + 1));
		if (!args)
		{
			perror("Error: memory allocation failure!\n");
			return (0);
		}
		token = cmdlist->head;
		i = 0;
		while(token)
		{
			if(token->type == ARG)
			{
				args[i++] = ft_strdup(token->value);
			}
			token = token->next;
    }
    args[i] = NULL;
    return (args);
}

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
			array[count] = ft_strfjoin(array[count], "=");
			array[count] = ft_strfjoin(array[count], node->value);
			count++;
		}
		node = node->next;
	}
	array[count] = NULL;
	return (array);
}
