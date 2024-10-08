/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:59:45 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/06 17:53:04 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(int number)
{
	size_t	num_len;

	num_len = 0;
	if (number == 0)
		num_len++;
	else if (number < 0)
	{
		num_len++;
		number *= -1;
	}
	while (number)
	{
		number /= 10;
		num_len++;
	}
	num_len++;
	return (num_len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	num;
	char	*num_conv;

	num = n;
	len = ft_numlen(n);
	num_conv = (char *)malloc(len * sizeof(char));
	if (num_conv == NULL)
		return (NULL);
	if (n == 0)
		num_conv[0] = '0';
	if (n < 0)
	{
		num_conv[0] = '-';
		num *= -1;
	}
	len--;
	num_conv[len--] = '\0';
	while (num)
	{
		num_conv[len--] = (num % 10) + 48;
		num /= 10;
	}
	return (num_conv);
}
/*
int	main(void)
{
	#include <stdio.h>

	char	*number_conv;
	int	n;
	char	*original_adress;

	n = -2147483648 ;
	//n = 0;
	//n = 2147483647;
	number_conv = ft_itoa(n);
	original_adress = number_conv;
	while (*number_conv)
	{
		printf("%c", *number_conv);
		number_conv++;
	}
	printf("\n");
	number_conv = original_adress;
	free(number_conv);
	return (0);
}*/
