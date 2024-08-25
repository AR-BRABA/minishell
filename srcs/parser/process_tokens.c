#include "../../includes/minishell.h"

enum e_type {
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_FILE,
	APPEND,
	HEREDOC
};

typedef struct	s_node {
	char	*value;
	int	type;
	struct s_node	*next;
}	t_node;

typedef struct	s_list {
	int	size;
	t_node	*head;
	t_node	*next;
}	t_list;

// typedef struct	s_table {
// 	char	**tokens;
// 	t_node	**frases;
// }	t_table;

t_node	*new_token()
{
	t_node	*token;

	token = malloc(sizeof(t_node));
	token->value = NULL;
	token->type = COMMAND;
	token->next = NULL;
	return (token);
}

t_list	*new_cmd(t_node *token)
{
	t_list	*cmd;

	cmd = malloc(sizeof(t_list));
	cmd->head = token;
	cmd->next = NULL;
	return (cmd);
}

void	set_value

t_list	*new_table(char **splitted_input)
{
	int	count;
	int	count2;
	t_node	*token;
	t_list	*table;
	t_list	*cmd;
	
	token = new_token();
	cmd = new_cmd(token);
	table = cmd;
	while (splitted_input != NULL)
	{
		token = new_token();
		if (!token)
			free;
		if (*splitted_input[0] == '|')
		{
			cmd = new_cmd(token);
		}
	}

}

t_list	*get_commands(char **tokens)
{
	int	count = 0;
	int	frases = 0;
	t_list	*cmdtable;
	
	
	return (cmdtable);
}

t_table	*get_cmdtable()
{

}
