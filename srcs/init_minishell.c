/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2024/12/05 18:48:21 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// missing: signals on forks and heredoc
void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_redisplay();
		// salvar exit statu
		// set_status(130);
	}
	return ;
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
				free(main->input);
				// free main->input??
				//tokenizer
				main->cmdtab = get_cmdtable(main->split, main->envp);
				free(main->split);
				// pipe still not integrated:
				execute_commands(main->cmdtab, main->envp, envp);
				// else
				free_table(main->cmdtab); // deallocate memory
				// free all
			}
			// handle errors
		}
	}
	return (0);
}
