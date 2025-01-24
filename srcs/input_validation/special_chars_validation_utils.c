/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:59:21 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/24 15:38:39 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redirects_followed_by_pipe(char *input)
{
	while (*input)
	{
		if ((*input == '>' || *input == '<'))
		{
			input++;
			skip_spaces(&input);
			if (*input == '|') // > ou < seguido de |
				return (false);
		}
		else
			input++;
	}
	return (true);
}

bool	pipe_followed_by_redirects(char *input)
{
	char	current_char;
	int		count;

	current_char = '\0';
	count = 0;
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			skip_spaces(&input);
			if (*input == '>' || *input == '<') // | seguido de > ou <
			{
				current_char = *input;
				count = 0;
				while (*input == current_char) // > ou < consecutivos depois de |
				{
					count++;
					input++;
				}
				if (count > 2) // + de dois > ou < consecutivos
					return (false);
			}
		}
		else
			input++;
	}
	return (true);
}

bool	consecutive_pipes(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			skip_spaces(&input);
			if (*input == '|')
				return (false);
		}
		else
			input++;
	}
	return (true);
}

bool	consecutive_redirects(char *input)
{
	char	current_char;
	int		count;

	current_char = '\0';
	count = 0;
	while (*input)
	{
		if (*input == '>' || *input == '<')
		{
			current_char = *input;
			count = 0;
			while (*input == current_char) // > ou < consecutivos
			{
				count++;
				input++;
			}
			if (count > 2) // + de 2 > ou < consecutivos
				return (false);
			skip_spaces(&input);
			if (*input == '>' || *input == '<')
				return (false);
		}
		else
			input++;
	}
	return (true);
}
