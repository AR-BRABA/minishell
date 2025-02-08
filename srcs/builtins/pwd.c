/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:46:13 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 09:46:16 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	buf[PATH_MAX + 1];
	char	*path;

	path = getcwd(buf, PATH_MAX + 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	if (!path)
		return (1);
	return (0);
}
