/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:50:52 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/24 21:26:55 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * readline() prints a prompt
 * @param char* prompt
 * @return char *line_read
 */

char	*read_input(char *user_input)
{
	user_input = readline("minishell$ ");
	if (user_input)
		add_history(user_input);
	return (user_input);
}
