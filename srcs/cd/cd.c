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

void	update_key_value(t_env *list, char *key, char *new_val)
{
	t_envnode *node;

	node = search_key(list, key);
	if (node && node->value)
	{
		free(node->value);
		node->value = ft_strdup(new_val);
	}
}

/* passar NULL se nao houver argumento */
//TODO: need to test!!
int	cd(char *dest, t_env *env)
{
	char	*origin;
	char	buf[PATH_MAX + 1];
	char	buf2[PATH_MAX + 1];
	int	ret;

	// origin = NULL;
	origin = getcwd(buf, PATH_MAX + 1);
	if (!origin)
		return (1);
	// origin = get_key_value(env, "PWD");
	if (dest[0] == '-')
		dest = get_key_value(env, "OLD_PWD");
	else if (dest[0] == '~' || !dest)
		dest = get_key_value(env, "HOME");
	ret = chdir(dest);
	if (ret != 0)
		return (1);
	update_key_value(env, "OLD_PWD", origin);
	// origin = NULL;
	origin = getcwd(buf2, PATH_MAX + 1);
	if (!origin)
		return (1);
	update_key_value(env, "PWD", origin);
	return (0);
}
