/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:00:39 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 14:03:23 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens(char *user_input)
{
	int		count;
	int		tokens;
	char	*input;

	count = 0;
	tokens = 0;
	input = strtrim_space(user_input);
	while (input && input[count] != '\0')
	{
		count = handle_operator(input, count);
		if (!is_metachar(input[count]))
			count = handle_non_metachar(input, count);
		tokens++;
		count = skip_spacesc(input, count);
	}
	free(input);
	return (tokens);
}

char	**metachar_split(char *user_input)
{
	int		count;
	int		start;
	int		token;
	char	**array;
	char	*input;

	count = 0;
	token = 0;
	input = strtrim_space(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	while (input && input[count] != '\0')
	{
		start = count;
		count = handle_operator(input, count);
		if (!is_metachar(input[start]))
			count = handle_non_metachar(input, count);
		else if (!is_space(input[start]))
			count = handle_non_space_split(input, count);
		array[token++] = substr_by_address(&input[start], (count - start));
		count = skip_spacesc(input, count);
	}
	array[token] = NULL;
	free(input);
	return (array);
}
