/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:03:00 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:42:14 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tempdest;
	const char	*tempsrc;

	tempdest = (char *)dest;
	tempsrc = (char *)src;
	if (dest > src)
	{
		while (n--)
			tempdest[n] = tempsrc[n];
	}
	else
		ft_memcpy(dest, src, n);
	return ((void *)dest);
}
