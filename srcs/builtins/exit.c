#include "../../includes/minishell.h"

// rl_clear_history on exit
int	ft_exit(char **args, t_env *env, t_tab *cmdtab)
{
	int	len = split_len(args);
	int	i = 0;
	int	nbr = 1;
	char *tmp;

	ft_putstr_fd("exit\n", 1);
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i] != '\0')
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
		{
			tmp = get_key_value(env, "?");
			nbr = ft_atoi(tmp); // trocar por atol
			free(tmp);
		}
	}
	free_split(args);
	free_env(env);
	free_table(cmdtab);
	exit (nbr);
}
