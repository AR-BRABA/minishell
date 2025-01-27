/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:12:01 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/27 18:20:48 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_list(t_node *head)
{
	int		count;
	t_node	*token;

	count = 0;
	token = head;
	while (token)
	{
		if (token->type == ARG)
			count++;
		token = token->next;
	}
	return (count);
}

char	**build_arg_split(t_node *token)
{
	int		i;
	char	**args;
	t_node	*arg_token;

	i = 0;
	arg_token = token;
	args = (char **)malloc(sizeof(char *) * (count_list(token) + 1));
	if (!args)
	{
		perror("Error: memory allocation failure!\n");
		return (NULL);
	}
	while (arg_token)
	{
		if (!arg_token->value)
		{
			free(args);
			return (0);
		}
		else if (token->type == ARG)
			args[i++] = ft_strdup(arg_token->value);
		arg_token = arg_token->next;
	}
	args[i] = NULL;
	return (args);
}

/*
 ** Converts the token linked list into a array of strings (char **) 
 */
char	**list_to_char_array(t_node *token)
{
	char	**args;

	if (!count_list(token))
		return (NULL);
	args = build_arg_split(token);
	return (args);
}

char	**get_args_array(t_list *cmdlist)
{
	int		i;
	char	**args;
	t_node	*token;

	args = (char **)malloc(sizeof(char *) * (count_list(cmdlist->head) + 1));
	if (!args)
	{
		perror("Error: memory allocation failure!\n");
		return (0);
	}
	token = cmdlist->head;
	i = 0;
	while (token)
	{
		if (token->type == ARG)
			args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

char	**env_to_char_array(t_env *envp)
{
	int			count;
	t_envnode	*node;
	char		**array;

	count = 0;
	if (!envp || !envp->head)
		return (NULL);
	array = malloc((envp->len + 1) * sizeof(char *));
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
