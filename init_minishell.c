/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/24 21:20:34 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */

int	main(void)
{
	char *user_input;

	while (1)
	{
		user_input = read_input(user_input);
		if (!user_input)
			break ;
		if (validate_input(user_input))
			printf("Valid input: %s\n", user_input);
	}
	return (0);
}
