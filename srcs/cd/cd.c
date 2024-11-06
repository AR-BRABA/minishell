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

/* passar NULL se nao houver argumento ou tratar fora!*/
int	cd(char *dest, t_env *env)
{
	char	*origin;
	char	*path;
	char	buf[PATH_MAX + 1];
	// char	buf2[PATH_MAX + 1];

	// precisa de free?
	if (!dest || ft_strncmp(dest, "~", 1) == 0)
	{
		path = get_key_value(env, "HOME");
		if (dest && dest[1] != '\0')
			path = ft_strfjoin(path, &dest[1]);	
	}
	else if (ft_strncmp(dest, "-", 2) == 0)
		path = get_key_value(env, "OLDPWD");
	else
		path = ft_strdup(dest);
	origin = getcwd(buf, PATH_MAX + 1);
	if (chdir(path) == -1)
	{
		free(path);
		// free(origin);?
		return (1);
	}
	update_key_value(env, "OLDPWD", origin);
	// origin = NULL;
	// free(origin);
	// path = getcwd(buf2, PATH_MAX + 1);
	update_key_value(env, "PWD", path);
	free(path);
	return (0);
}
