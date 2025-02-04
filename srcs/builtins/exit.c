#include "../../includes/minishell.h"
#include <readline/readline.h>

int	ft_atou(const char *nptr)
{
	int		i;
	long		convnum;
	unsigned	ret;
	int		sign;

	i = 0;
	convnum = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		convnum = convnum * 10 + (nptr[i] - 48);
		i++;
	}
	ret = convnum *sign;
	return (ret);
}

/*
int	check_digits(char **args)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break ;
		}
		i++;
	}
	if (!nbr || i >= 20)
		return (2);
	return (1);
}

int	ft_exit(char **args, t_main *main)
{
	int		nbr;
	char	*tmp;

	ft_putstr_fd("exit\n", 1);
	nbr = check_digits(args);
	if (nbr == 2)
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	else
	{
		if (split_len(args) > 1)
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
				1);
		if (split_len(args) == 1)
			nbr = ft_atou(args[0]);
		else
		{
			tmp = get_key_value(main->envp_list, "?");
			nbr = ft_atou(tmp);
			free(tmp);
		}
	}
	rl_clear_history();
	close(main->fd[0]);
	close(main->fd[1]);
	free_split(args);
	free_main(main);
	exit(nbr);
}

int	ft_atou(const char *nptr)
{
	int			i;
	long		convnum;
	unsigned	ret;
	int			sign;

	i = 0;
	convnum = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		convnum = convnum * 10 + (nptr[i] - 48);
		i++;
	}
	ret = convnum * sign;
	return (ret);
}
/*
int	check_digits(char **args)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break ;
		}
		i++;
	}
	if (!nbr || i >= 20)
		return (2);
	return (1);
}

int	ft_exit(char **args, t_main *main)
{
	int		nbr;
	char	*tmp;

	ft_putstr_fd("exit\n", 1);
	nbr = check_digits(args);
	if (nbr == 2)
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	else
	{
		if (split_len(args) > 1)
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
				1);
		if (split_len(args) == 1)
			nbr = ft_atou(args[0]);
		else
		{
			tmp = get_key_value(main->envp_list, "?");
			nbr = ft_atou(tmp);
			free(tmp);
		}
	}
	rl_clear_history();
	close(main->fd[0]);
	close(main->fd[1]);
	free_split(args);
	free_main(main);
	exit(nbr);
}

int	ft_exit(char **args, t_main *main)
{
	int		len;
	int		i;
	int		nbr;
	char	*tmp;

	len = split_len(args);
	i = 0;
	nbr = 1;
	ft_putstr_fd("exit\n", 1);
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i] != '\0')
	{
		if (!ft_isdigit(args[0][i]))
		{
			nbr = 0;
			break ;
		}
		i++;
	}
	if (!nbr || i >= 20)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		nbr = 2;
	}
	else
	{
		if (len > 1)
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
				1);
		if (len == 1)
			nbr = ft_atou(args[0]);
		else
		{
			tmp = get_key_value(main->envp_list, "?");
			nbr = ft_atou(tmp);
			free(tmp);
		}
	}
	rl_clear_history();
	close(main->fd[0]);
	close(main->fd[1]);
	free_main(main);
	free_split(args);
	exit(nbr);
}

int	ft_exit_nbr(int nbr, t_main *main)
{
	rl_clear_history();
	free_main(main);
	exit(nbr);
}
*/
static int	is_valid_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg && arg[i] == '-')
		i++;
	while (arg && arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (i != 0 && i < 20);
}

static int	get_exit_status(char **args, t_main *main)
{
	int		nbr;
	char	*tmp;

	if (split_len(args) == 1)
		nbr = ft_atou(args[0]);
	else
	{
		tmp = get_key_value(main->envp_list, "?");
		nbr = ft_atou(tmp);
		free(tmp);
	}
	return (nbr);
}

int	ft_exit(char **args, t_main *main)
{
	int	nbr;

	nbr = 1;
	ft_putstr_fd("exit\n", 1);
	if (sigint != -24)
		nbr = sigint;
	else if (args && split_len(args) > 0 && !is_valid_exit_arg(args[0]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		nbr = 2;
	}
	else if (args && split_len(args) > 1)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	else
		nbr = get_exit_status(args, main);
	rl_clear_history();
	close(main->fd[0]);
	close(main->fd[1]);
	free_main(main);
	free_split(args);
	exit(nbr);
}

int	ft_exit_nbr(int nbr, t_main *main)
{
	rl_clear_history();
	free_main(main);
	exit(nbr);
}
