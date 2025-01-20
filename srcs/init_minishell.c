/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/16 00:57:00 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_redisplay();
	}
}

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */
int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
	char	*input;
	char	**split;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	//user_input = NULL;
	// builds env linked list
	main = malloc(sizeof(t_main));
	main->envp_list = get_env_list(envp);
	main->envp = env_to_char_array(main->envp_list);
	while (1) // or could 'user_input = readline("minishell$ ")' be the while condition? check if this respects the 42 norm
	{
		input = readline("minishell$ ");
		if (!input)
			break; // Stop the loop if readline() returns NULL (EOF)
		else if (input && !check_empty_input(input))
		{
			if (validate_input(input))
			{
				//printf("Valid input: %s\n", user_input);
				add_history(input);
				//lexer
				split = metachar_split(input);
				free(input);
				// free main->input??
				//tokenizer
				main->cmdtab = get_cmdtable(split, main->envp_list);
				free(split);
				// pipe still not integrated:
				execute_commands(main);
				// else
				free_table(main->cmdtab); // deallocate memory
				// free all
			}
			// handle errors
		}
	}
	free_split(main->envp);
	free_env(main->envp_list);
	free(main);
	return (0);
}
