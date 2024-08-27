/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/07/10 23:50:01 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */

int	main(void)
{
	char	*user_input;

	user_input = NULL;
	while (1) // or could 'user_input = readline("minishell$ ")' be the while condition? check if this respects the 42 norm
	{
		user_input = readline("minishell$ ");
		if (!user_input)
			break; // Stop the loop if readline() returns NULL (EOF)
		if (user_input && !has_only_spaces(user_input))
		{
			if (validate_input(user_input))
				printf("Valid input: %s\n", user_input);
			add_history(user_input);
		}
		// cal lexer to process token
		free(user_input);
	}
	return (0);
}
