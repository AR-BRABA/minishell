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
	char	*input;

	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	if (pipe(fd) < 0)
	{
		perror(token->next->value);
		return (1);
	}
	input = readline("> ");
	while (ft_strncmp(input, token->next->value, ft_strlen(token->next->value)
			+ 1) != 0)
	{
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
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
	list->fd[2] = -1;
	token = list->head;
	while (token != NULL && token->next != NULL)
	{
		if (token->type == REDIRECT_IN)
		{
			list->fd[2] = 0;
			if (pre_redirect_in(token, list->fd) == 1)
				return (1);
		}
		else if (token->type == HEREDOC)
		{
			list->fd[2] = 1;
			if (pre_heredoc(token, list->fd) == 1)
				return (1);
		}
		else if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			list->fd[2] = 0;
			if (pre_redirect_out(token, list->fd) == 1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
