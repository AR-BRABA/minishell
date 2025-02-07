/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:59:50 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/06 22:00:05 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_metachar(char c)
{
	return (is_operator(c) || is_space(c));
}

/* returns if is a valid name for an enviroment variable ([a-z], [A-Z], '_',
		[0-9]) */
int	is_name(char c)
{
	return ((c == '_') || ft_isalnum(c));
}
