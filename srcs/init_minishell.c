/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/23 09:34:35 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	//add to env - global
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_redisplay();
	}
}

t_main	*init_main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = malloc(sizeof(t_main));
	main->envp_list = get_env_list(envp);
	main->envp = env_to_char_array(main->envp_list);
	main->fd[0] = -1;
	main->fd[1] = -1;
	return (main);
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
	main = init_main(argc, argv, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input || !validate_input(input))
			break ;
		else if (input && !has_only_spaces(input))
		{
			add_history(input);
			split = metachar_split(input);
			free(input);
			main->cmdtab = get_cmdtable(split, main->envp_list);
			free(split);
			execute_commands(main);
			main->cmdtab = free_table(main->cmdtab);
		}
	}
	free_main(main);
	return (0);
}
