/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/08 18:38:44 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*user_input;
	char	**split;
	t_tab	*cmdtab;

	(void)argc;
	(void)argv;
	//user_input = NULL;
	// builds env linked list
	env = get_env_list(envp);
	while (1) // or could 'user_input = readline("minishell$ ")' be the while condition? check if this respects the 42 norm
	{
		user_input = readline("minishell$ ");
		if (!user_input)
			break; // Stop the loop if readline() returns NULL (EOF)
		else if (user_input && !has_only_spaces(user_input))
		{
			if (validate_input(user_input))
			{
				//printf("Valid input: %s\n", user_input);
				add_history(user_input);
				//lexer
				split = metachar_split(user_input);
				//tokenizer
				cmdtab = get_cmdtable(split, env);
				//expand and remove quotes (work in progress)
				format(cmdtab, env);
				execute_commands(cmdtab); // call executor
				destroy_table(cmdtab); // deallocate memory
			}
			// handle errors
		}
		free(user_input);
	}
	return (0);
}
