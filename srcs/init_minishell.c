/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 17:04:33 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_tecno_status = -24;

void	print_tab(t_tab *table)
{
	t_list	*list;
	int		size;
	int		count;

	if (!table)
	{
		printf("No tabLe!!\n");
		return ;
	}
	list = table->head;
	if (!list)
	{
		printf("Head empty!!\n");
		return ;
	}
	size = 0;
	while (list != NULL)
	{
		printf("\n");
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		printf("-----------------------------------\n");
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		printf("len = %i\n", list->len);
		count = 0;
		while (count < size)
		{
			printf("\t");
			count++;
		}
		size++;
		print_list(list);
		list = list->next;
	}
}

void	print_list(t_list *list)
{
	t_node	*node;

	node = list->head;
	if (!node)
	{
		printf("no list!!\n\n");
		return ;
	}
	node = list->head;
	while (node != NULL)
	{
		printf("{value = !%s! \\ type = %i}->", node->value, node->type);
		node = node->next;
	}
	printf("NULL\n");
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_redisplay();
		g_tecno_status = 128 + SIGINT;
	}
}

t_main	*init_main(int argc, char **argv, char **envp)
{
	t_main	*main;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	main = malloc(sizeof(t_main));
	main->envp_list = get_env_list(envp);
	main->envp = env_to_char_array(main->envp_list);
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

	main = init_main(argc, argv, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		else if (check_empty_input(input) || !validate_input(input))
			continue ;
		add_history(input);
		split = metachar_split(input);
		free(input);
		main->cmdtab = get_cmdtable(split, main->envp_list);
		free(split);
		execute_commands(main);
		free_table(main->cmdtab);
		main->cmdtab = NULL;
	}
	free_main(main);
	return (0);
}
