#include "../../includes/minishell.h"

t_envnode	*new_envnode(char *envp)
{
	char	**split;
	t_envnode	*node;
	
	split = ft_split(envp, '=');
	if (!split || !split[0] || ft_strlen(split[0]) != strlen_isname(split[0]))
		return (NULL);
	node = malloc(sizeof(t_envnode));
	node->key = split[0];
	node->value = split[1];
	node->prev = NULL;
	node->next = NULL;
	free(split);
	return (node);
}

void	addback_env(t_envnode *newnode, t_env *list)
{
	t_envnode	*node;

	node = list->head;
	if (!node)
	{
		list->head = newnode;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	newnode->prev = node;
	node->next = newnode;
	list->len++;
}

t_env	*get_env_list(char **envp)
{
	int	i = 0;
	t_env	*env;
	t_envnode	*node;

	if (!envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->len = 0;
	env->head = NULL;
	env->tail = env->head;
	while (envp[i] != NULL)
	{
		node = new_envnode(envp[i]);
		addback_env(node, env);
		i++;
	}
	env->tail = node;
	return (env);
}

int	env(t_env *env)
{
	t_envnode	*node;
	
	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		ft_putstr_fd(node->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(node->value, 1);
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
	return (0);
}

/* validate outside */
int	envexport(char *input, t_env *env)
{
	t_envnode	*node;
	
	node = new_envnode(input);
	if (!node)
		return (1);
	addback_env(node, env);
	return(0);
}


int	envunset(char *key, t_env *env)
{
	t_envnode	*node;
	
	node = search_key(env, key);
	if (!node)
		return (1);
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
	return (0);
}
// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env	*env;
//
// 	env = get_env_list(envp);
// 	print_env(env);
// 	return(0);
// }
