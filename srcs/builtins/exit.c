/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:46:27 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 00:24:13 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atou(const char *nptr)
{
	int				i;
	long			convnum;
	unsigned int	ret;
	int				sign;

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
	if (g_tecno_status != -24)
		nbr = g_tecno_status;
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
