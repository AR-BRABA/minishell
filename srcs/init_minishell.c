/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/11/10 00:00:42 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// rl_clear_history on exit
// missing: signals on forks and heredoc
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
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

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	//user_input = NULL;
	// builds env linked list
	main = malloc(sizeof(t_main));
	main->envp = get_env_list(envp);
	while (1) // or could 'user_input = readline("minishell$ ")' be the while condition? check if this respects the 42 norm
	{
		main->input = readline("minishell$ ");
		if (!main->input)
			break; // Stop the loop if readline() returns NULL (EOF)
		else if (main->input && !has_only_spaces(main->input))
		{
			if (validate_input(main->input))
			{
				//printf("Valid input: %s\n", user_input);
				add_history(main->input);
				//lexer
				main->split = metachar_split(main->input);
				//tokenizer
				main->cmdtab = get_cmdtable(main->split, main->envp);
				//expand and remove quotes (work in progress)
				format(main->cmdtab, main->envp);
				execute_commands(main->cmdtab, main->envp); // call executor
				free_table(main->cmdtab); // deallocate memory
			}
			// handle errors
		}
		free(main->input);
	}
	return (0);
}
