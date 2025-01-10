#include "../../includes/minishell.h"

int	ft_export(char **args, t_env *env)
{
	int	ret = 0;
	int	count = 0;
	t_envnode	*node;
	
	while (args && args[count] != NULL)
	{
		// TODO: validar caso de prompt '1asd' nao printar erro
		node = new_envnode(args[count]);
		if (node && str_isname(node->key))
			addback_env(node, env);
		else if (node)
		{
			ret = ft_error("export", node->key, "not a valid identifier", 1);
			free(node->key);
			free(node->value);
			free(node);
		}
		else
			ret = 1;
		count++;
	}
	return(ret);
}
