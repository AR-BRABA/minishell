#include "../../includes/minishell.h"

typedef struct	s_envnode {
	char	*key;
	char	*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
} t_envnode;

typedef struct	s_env {
	int	len;
	t_envnode	*head;
	t_envnode	*tail;
} t_env;

t_envnode	*new_envnode(char *envp)
{
	char	**split;
	t_envnode	*node;
	
	split = ft_split(envp, '=');
	node = malloc(sizeof(t_envnode));
	node->key = split[0];
	node->value = split[1];
	node->prev = NULL;
	node->next = NULL;
	free(split);
	return (node);
}

void	addback_env(t_envnode *new, t_env *list)
{
	t_envnode	*node;

	node = list->head;
	if (!node)
	{
		list->head = new;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	new->prev = node;
	node->next = new;
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

// essa func eh o builtin do env, mudar a formatacao pra ficar igual ao env
void	print_env(t_env	*env)
{
	t_envnode	*node;
	
	if (!env)
	{
		printf("no env!!");
		return;
	}
	printf("total env = %i\n", env->len);
	node = env->head;
	while (node != NULL)
	{
		printf("key: %s            value: %s\n", node->key, node->value);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;

	env = get_env_list(envp);
	print_env(env);
	return(0);
}
