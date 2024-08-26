/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:36 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/16 06:19:16 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		s_pos;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s_pos = 0;
	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2[s_pos] != '\0')
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	return (s);
}
/*
int	main(void)
{
	#include <stdio.h>

	char const *str1;
	char const *str2;
	char    *str;

	str1 =  "Você só dança com ele ";
	str2 = "e diz que é sem compromisso";
	str = ft_strjoin(str1, str2);
	printf("%s\n", str);
	return (0);
}*/
