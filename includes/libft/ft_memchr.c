/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:21:01 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:40:56 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temps;
	size_t			i;

	temps = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temps[i] != (unsigned char)c)
			i++;
		else
			return ((void *)(s + i));
	}
	return (NULL);
}
