/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 05:25:03 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:48:29 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;
	char	*str;

	length = ft_strlen(s);
	str = (char *)s;
	if (!str)
		return (NULL);
	if (str[length] == (unsigned char)c)
		return ((char *)(s + length));
	while (length != 0)
	{
		if (s[length - 1] == (unsigned char)c)
			return ((char *)(s + (length - 1)));
		length--;
	}
	return (NULL);
}
