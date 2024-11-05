#include "../../includes/minishell.h"

t_envnode	*new_envnode(char *envp)
{
	char	**split;
	t_envnode	*node;
	
	split = ft_split(envp, '='); //FIX: splitar apenas ate o primeiro =
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
		list->tail = newnode;
		list->len++;
		return ;
	}
	node = list->tail;
	newnode->prev = node;
	node->next = newnode;
	list->tail = newnode;
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
	env->envp = envp;
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

int	minienv(t_env *env)
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
		//validate args here
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

char	*ft_getenv(t_env *list, char *key)
{
	int	len = ft_strlen(key);
	t_envnode	*env;

	env = list->head;
	while (env != NULL)
	{
		//compare key with env variables on list
		if (ft_strncmp(key, env->key, len + 1) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_strdup(env->value));
}

int	mini_exit(char **args, t_env *env, t_tab *cmdtab)
{
	int	nbr;

	if (args)
		nbr = ft_atoi(args[0]);
	else
		nbr = ft_atoi(ft_getenv(env, "?"));
	destroy_env(env);
	destroy_table(cmdtab);
	exit(nbr);
}

// se args eh letra -> executa e retorna 2
// "Error: exit: numeric argument required", 2
// se args > 1 -> retorna 1 e nao executa
// "Error: exit: too many arguments", 2
// a ordem importa. se for: a b, o erro sera: numeric argument required
// passar a struct main!!!
// usar essa versao com a struct principal:
//
// int	ft_exit(char *arg, t_main *main)
// {
// 	int	nbr;
//
// 	if (arg)
// 		nbr = ft_atoi(arg);
// 	else
// 		nbr = ft_atoi(ft_getenv(main->envp, "?"));
// 	free_split(main->split);
// 	destroy_env(main->envp);
// 	destroy_table(main->cmdtab);
// 	free(main);
// 	return (nbr);
// }
