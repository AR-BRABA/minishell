/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:31:39 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/21 23:53:30 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	end_substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len < start + len)
		end_substr = s_len;
	else
		end_substr = start + len;
	substr = (char *)malloc((end_substr - start + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (start < end_substr)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
/*
int	main(void)
{
	#include <stdio.h>

	char const	*str = "lorem ipsum dolor sit amet";
	unsigned int	st = 0;
	size_t		length = 10;
	char		*sub_str;
	int		i;

	sub_str = ft_substr(str, st, length);
	i = 0;
	printf("%s\n", sub_str);
	return (0);
}*/
