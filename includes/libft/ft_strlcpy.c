/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:03:18 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:46:34 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			src_len;
	unsigned char	*source;

	i = 0;
	src_len = ft_strlen(src);
	source = (unsigned char *)src;
	if (size == 0)
		return (src_len);
	while (source[i] && i < (size - 1))
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
