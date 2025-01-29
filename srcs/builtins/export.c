#include "../../includes/minishell.h"

void	update_env(char *key, char *value, t_env *envp)
{
	t_envnode	*node;
	
	node = search_key(envp, key);
	free(node->value);
	node->value = ft_strdup(value);
}

void	update_envnode(char *value, t_envnode *node)
{
	free(node->value);
	node->value = ft_strdup(value);
}

int	handle_existing_key(t_envnode *new, t_envnode *old)
{
	if (old)
		update_envnode(new->value, old);
	else
	{
		perror("export:");
		return (1);
	}
	free_envnode(new);
	return (0);
}

int	ft_export(char **args, t_env *envp)
{
	int	ret = 0;
	int	count = 0;
	t_envnode	*new;
	t_envnode	*old;
	
	while (args && args[count] != NULL)
	{
		new = new_envnode(args[count++]);
		if (!new)
			return (1);
		old = search_key(envp, new->key);
		if (!old && str_isname(new->key) && !ft_isdigit(new->key[0]))
			addback_env(new, envp);
		else
			ret = handle_existing_key(new, old);
	}
	return(ret);
}