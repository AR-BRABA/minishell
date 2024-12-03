#include "../../includes/minishell.h"

// test
int	ft_export(char **args, t_env *envp)
{
	int	ret = 0;
	int	count = 0;
	t_envnode	*new;
	t_envnode	*old;
	
	while (args && args[count] != NULL)
	{
		new = new_envnode(args[count]);
		if (!new)
			return (1);
		old = search_key(envp, new->key);
		if (!old && str_isname(new->key) && !ft_isdigit(new->key[0]))
		{
			addback_env(new, envp);
			ret = 0;
		}
		else if (old)
		{
			free(old->value);
			old->value = ft_strdup(new->value);
			free(new->key);
			free(new->value);
			free(new);
		}
		else
		{
			ret = ft_error("export", new->key, "not a valid identifier", 1);
			free(new->key);
			free(new->value);
			free(new);
		}
		count++;
	}
	return(ret);
}

// test
void	update_exit_status(int status, t_env *envp)
{
	t_envnode	*node;
	
	node = search_key(envp, "?");
	free(node->value);
	node->value = ft_strdup(ft_itoa(status));
}
