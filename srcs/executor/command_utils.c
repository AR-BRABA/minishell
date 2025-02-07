#include "../../includes/minishell.h"

t_node	*get_cmd(t_list *cmdlist)
{
	t_node	*token;

	token = cmdlist->head;
	while (token != NULL)
	{
		if (token->type == COMMAND)
			return (token);
		token = token->next;
	}
	return (NULL);
}