#include "../../includes/minishell.h"

int	echo(char **arg)
{
	int	n = 0;
	int	i;

	if (arg && arg[0] && ft_strncmp(arg[0], "-n", 2) == 0)
		n++;
	i = n;
	while (arg && arg[i])
	{
		ft_putstr_fd(arg[i++], 1);
		if (arg[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}
