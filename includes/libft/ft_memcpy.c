/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:47:48 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:41:36 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tempdest;
	unsigned char	*tempsrc;
	size_t			i;

	tempdest = (unsigned char *)dest;
	tempsrc = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	while (i < n)
	{
		tempdest[i] = tempsrc[i];
		i++;
	}
	return ((void *)dest);
}
