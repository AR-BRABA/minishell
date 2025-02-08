/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:48:29 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 09:48:31 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(char *cmd, char *arg, char *message, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	if (message)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	str_isname(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (((i == 0 && ft_isdigit(str[i])) || !is_name(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	return (i);
}
