/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:29:40 by tsoares-          #+#    #+#             */
/*   Updated: 2023/11/23 20:07:13 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *full_str, char delimiter)
{
	int		num_words;
	size_t	i;

	num_words = 0;
	i = 0;
	while (full_str[i])
	{
		while (full_str[i] && full_str[i] == delimiter)
			i++;
		if (full_str[i] && full_str[i] != delimiter)
		{
			num_words += 1;
			while (full_str[i] && full_str[i] != delimiter)
				i++;
		}
	}
	return (num_words);
}

static char	*ft_malloc_word(const char *str, size_t s_pos, char c_del)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (str[s_pos] && str[s_pos] != c_del)
	{
		word_len++;
		s_pos++;
	}
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	s_pos -= word_len;
	word_len = 0;
	while (str[s_pos] && str[s_pos] != c_del)
	{
		word[word_len] = str[s_pos];
		word_len++;
		s_pos++;
	}
	word[word_len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	arr_pos;
	size_t	str_pos;

	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	str_pos = 0;
	arr_pos = 0;
	while (s[str_pos] && arr_pos < ft_count_words(s, c))
	{
		while (s[str_pos] && s[str_pos] == c)
			str_pos++;
		if (s[str_pos] != c)
			arr[arr_pos++] = ft_malloc_word(s, str_pos, c);
		if (!arr[arr_pos - 1])
			return (NULL);
		while (s[str_pos] && s[str_pos] != c)
			str_pos++;
	}
	arr[arr_pos] = NULL;
	return (arr);
}
