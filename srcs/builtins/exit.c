#include "../../includes/minishell.h"

int	ft_exit(char **args, t_env *env, t_tab *cmdtab)
{
	int	len = split_len(args);
	int	i = 0;
	int	nbr = 1;

	ft_putstr_fd("exit\n", 1);
	if (args[0][i] == '-')
		i++;
	while (args && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break;
		}
		i++;
	}
	if (!nbr || i >= 20)
		nbr = ft_error("exit", args[0], "numeric argument required", 2);
	else
	{
		if (len > 1)
			return (ft_error("exit", NULL, "too many arguments", 1));
		if (len == 1)
			nbr = ft_atoi(args[0]); // trocar por atol
		else
			nbr = ft_atoi(get_key_value(env, "?")); // trocar por atol
	}
	free_split(args);
	free_env(env);
	free_table(cmdtab);
	exit (nbr);
}
