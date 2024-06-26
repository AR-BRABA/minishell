/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:29:45 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 07:38:18 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalsz;
	void	*ptr_arr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	totalsz = nmemb * size;
	if (totalsz == 0)
		totalsz = 1;
	if (totalsz / nmemb != size)
		return (NULL);
	ptr_arr = (void *)malloc(totalsz);
	if (!ptr_arr)
		return (NULL);
	ft_memset(ptr_arr, 0, totalsz);
	return (ptr_arr);
}
