#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	buf[PATH_MAX + 1];
	char	*path;

	path = getcwd(buf, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	if (!path)
		return (1);
	return (0);
}
