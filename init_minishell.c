/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/06/22 01:00:44 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */

int	main(int argc, char **argv)
{
	while (1)
	{
		read_input(argv);
		if (!argv)
			break ;
		if (validate_input(*argv))
			printf("Valid input: %s\n", *argv);
	}
	(void)argc;
	return (0);
}
