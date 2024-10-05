#include "../../includes/minishell.h"

char	*get_key_value(t_env *list, char *key)
{
	char	*val;
	t_envnode *node;

	node = search_key(list, key);
	if (node)
		val = ft_strdup(node->value);
	else
		val = NULL;
	return (val);
}

void	update_key_value(t_env *list, char *key, char *value)
{
	t_envnode *node;

	node = search_key(list, key);
	if (node && node->value)
	{
		free(node->value);
		node->value = value;
	}
}

/* passar NULL se nao houver argumento */
int	cd(char *destpath, t_env *env)
{
	char	*curpath;
	int	ret;

	curpath = get_key_value(env, "PWD");
	if (destpath[0] == '-')
		destpath = get_key_value(env, "OLD_PWD");
	else if (destpath[0] == '~' || !destpath)
		destpath = get_key_value(env, "HOME");
	ret = chdir(destpath);
	if (ret != 0)
		return (1);
	update_key_value(env, "OLD_PWD", curpath);
	update_key_value(env, "PWD", destpath);
	return (0);
}
