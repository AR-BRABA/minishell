/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:43:40 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 15:28:23 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pre_redirect_out(t_node *token, int *fd)
{
	if (fd[1] != 1)
		close(fd[1]);
	if (token->type == APPEND)
		fd[1] = open(token->next->value, O_CREAT | O_APPEND | O_RDWR, 0664);
	else
		fd[1] = open(token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0664);
	if (fd[1] < 0)
	{
		perror(token->next->value);
		return (1);
	}
	return (0);
}

int	pre_heredoc(t_node *token, int *fd)
{
	int		fdh[2];
	char	*input;

	if (fd[0] != 0)
		close(fd[0]);
	if (pipe(fdh) < 0)
	{
		perror(token->next->value);
		return (1);
	}
	input = readline("> ");
	while (ft_strncmp(input, token->next->value, ft_strlen(token->next->value)
			+ 1) != 0)
	{
		write(fdh[1], input, ft_strlen(input));
		write(fdh[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(fdh[1]);
	fd[0] = fdh[0];
	return (0);
}

int	pre_redirect_in(t_node *token, int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	fd[0] = open(token->next->value, O_RDONLY);
	if (fd[0] < 0)
	{
		perror(token->next->value);
		return (1);
	}
	token = token->next->next;
	return (0);
}

int	pre_exec(t_list *list)
{
	t_node	*token;

	list->fd[0] = 0;
	list->fd[1] = 1;
	token = list->head;
	while (token != NULL && token->next != NULL)
	{
		if (token->type == REDIRECT_IN)
		{
			if (pre_redirect_in(token, list->fd) == 1)
				return (1);
		}
		else if (token->type == HEREDOC)
		{
			if (pre_heredoc(token, list->fd) == 1)
				return (1);
		}
		else if (token->type == REDIRECT_OUT || token->type == APPEND)
			if (pre_redirect_out(token, list->fd) == 1)
				return (1);
		token = token->next;
	}
	return (0);
}
