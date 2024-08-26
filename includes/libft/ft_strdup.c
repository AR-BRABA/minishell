/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 04:19:00 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/25 19:14:23 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	else
		dest = ft_strcpy(dest, s);
	return (dest);
}
/*
int	main(void)
{
	char	*source;
	char	*destiny;
	int		i;

	source = "Outro mundo";
	destiny = ft_strdup(source);
	i = 0;
	while (destiny[i])
	{
		write(1, &destiny[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}*/
