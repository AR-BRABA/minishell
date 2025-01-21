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

int	put_newnode(t_envnode *new, t_env *envp)
{
	int			ret;
	t_envnode	*old;

	ret = 0;
	old = search_key(envp, new->key);
	if (!old && str_isname(new->key) && !ft_isdigit(new->key[0]))
		addback_env(new, envp);
	else
	{
		if (old)
			update_envnode(new->value, old);
		else
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			ret = 1;
		}
		free_envnode(new);
	}
	return (ret);
}

int	ft_export(char **args, t_env *envp)
{
	int			ret;
	int			count;
	t_envnode	*new;

	ret = 0;
	count = 0;
	while (args && args[count] != NULL)
	{
		new = new_envnode(args[count++]);
		if (!new)
			return (1);
		ret += put_newnode(new, envp);
	}
	return (ret);
}
