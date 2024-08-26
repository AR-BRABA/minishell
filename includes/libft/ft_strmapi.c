/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:06:01 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/13 10:57:54 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	char			*new_str;
	unsigned int	i;
	char			transformed_char;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		transformed_char = f(i, s[i]);
		new_str[i] = transformed_char;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
int	main(void)
{
	#include <stdio.h>

>>> You can use this function to test my code, if you want.
char    personalized_toupper(unsigned int index, char c)
{
        if (index % 2 == 0)
                {
                        if (c > 96 && c < 123)
                                c -= 32;
                }
        return (c);
}


	char const	*str;
	char		*upper_str;

	str = "Onda, onda, olha a onda! ";
	upper_str = ft_strmapi(str, &personalized_toupper);
	printf("%s\n", upper_str);
	free (upper_str);
	return (0);
}*/
