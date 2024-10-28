#include "../../includes/minishell.h"

int	pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	ft_putstr_fd(buf, 1); // substituir 1 por STDOUT
	ft_putstr_fd("\n", 1); // substituir 1 por STDOUT
	if (!buf)
		return (1);
	free(buf);
	return (0);
}
