#include "../../includes/minishell.h"

t_envnode	*new_envnode(char *envp)
{
	char	**split;
	t_envnode	*node;
	
	split = ft_split(envp, '=');
	if (!split || !split[0] || (int)ft_strlen(split[0]) != strlen_isname(split[0]))
		return (NULL);
	node = malloc(sizeof(t_envnode));
	if (!node)
		return (NULL);
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
	env->envp = envp; // Armazenar envp p/usar na exec de cmds externos
	while (envp[i] != NULL)
	{
		node = new_envnode(envp[i]);
		addback_env(node, env);
		i++;
	}
	node = new_envnode("?=0");
	addback_env(node, env);
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
		if (node->key[0] != '?')
		{
			ft_putstr_fd(node->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(node->value, 1);
			ft_putchar_fd('\n', 1);
		}
		node = node->next;
	}
	return (0);
}

//TODO: erro chave nao eh valida
int	export(char **args, t_env *env)
{
	int	count = 0;
	t_envnode	*node;
	
	while (args && args[count] != NULL)
	{
		node = new_envnode(args[count]);
		if (node)
			addback_env(node, env);
		count++;
	}
	return(0);
}

//FIX: not working
int	unset(char **args, t_env *env)
{
	int	count = 0;
	t_envnode	*node;
	
	while (args && args[count] != NULL)
	{
		node = search_key(env, args[count]);
		if (!node)
			return (1);
		if (node->next)
			node->next->prev = node->prev;
		if (node->prev)
			node->prev->next = node->next;
		free(node->key);
		free(node->value);
		free(node);
		count++;
	}
	return (0);
}

int	destroy_env(t_env *env)
{
	t_envnode	*node;
	t_envnode	*temp;
	
	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		temp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(env);
	return (0);
}

/* tem mais coisa mallocada? */
int	mini_exit(char **args, t_env *env, t_tab *cmdtab)
{
	int	i = 0;
	int	nbr = 0;

	if (args && args[0] && args[1] != NULL)
	{
		ft_putstr_fd("Error: exit: too many arguments", 2);
		return (1);
	}
	while (args && args[0] && args[0][i] != '\0')
	{
		if (ft_isdigit(args[0][i]) != 0 || (i != 0 && args[0][i] == '-'))
		{
			ft_putstr_fd("Error: exit: numeric argument required", 2);
			destroy_env(env);
			destroy_table(cmdtab);
			exit(2);
		}
		i++;
	}
	if (args)
		nbr = ft_atoi(args[0]);
	destroy_env(env);
	destroy_table(cmdtab);
	exit(nbr);
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
