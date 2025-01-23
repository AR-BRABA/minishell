#include "../../includes/minishell.h"

t_tab	*get_cmdtable(char **input, t_env *env)
{
	int		i;
	t_list	*list;
	t_tab	*cmdtable;

	i = 0;
	cmdtable = init_cmdtab(input);
	if (!cmdtable)
		return (NULL);
	i += cmdlen(input);
	while (input[i] != NULL)
	{
		list = new_list(&input[i]);
		if (!list)
		{
			free_list(list);
			free_table(cmdtable);
			return (NULL);
		}
		add_list(list, cmdtable);
		i += cmdlen(&input[i]);
	}
	identify_tokens(cmdtable);
	format(cmdtable, env);
	return (cmdtable);
}
