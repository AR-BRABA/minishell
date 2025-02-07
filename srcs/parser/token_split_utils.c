/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:38:19 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 13:38:41 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operator(char *input, int count)
{
	if (is_operator(input[count]))
	{
		count++;
		if (is_operator(input[count]) && input[count] == input[count - 1])
			count++;
	}
	return (count);
}

int	handle_non_metachar(char *input, int count)
{
	int	quote;

	while (input[count] != '\0' && !is_metachar(input[count]))
	{
		if (is_quote(input[count]))
		{
			quote = count++;
			while (input[count] != input[quote])
				count++;
		}
		count++;
	}
	return (count);
}

int	skip_spacesc(char *input, int count)
{
	while (is_space(input[count]))
		count++;
	return (count);
}

int	handle_non_space_split(char *input, int count)
{
	while (input[count] != '\0' && !is_metachar(input[count])
		&& !is_quote(input[count]))
		count++;
	return (count);
}
