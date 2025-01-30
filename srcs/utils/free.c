#include "../../includes/minishell.h"

void	free_main(t_main *main)
{
	free_split(main->envp);
	free_env(main->envp_list);
	if (main->cmdtab)
		free_table(main->cmdtab);
	free(main);
}

void	free_envnode(t_envnode	*node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_tab	*free_table(t_tab *cmdtable)
{
	t_list	*cmdline;
	t_list	*nextline;

	if (!cmdtable)
		return (NULL);
	cmdline = cmdtable->head;
	while (cmdline != NULL)
	{
		nextline = cmdline->next;
		free_list(cmdline);
		cmdline = nextline;
	}
	free(cmdtable);
	cmdtable = NULL;
	return (NULL);
}

void	free_list(t_list *cmdline)
{
	t_node	*token;
	t_node	*tmptoken;

	token = cmdline->head;
	while (token != NULL)
	{
		tmptoken = token->next;
		free(token->value);
		free(token);
		token = tmptoken;
	}
	free(cmdline);
}

int	free_env(t_env *env)
{
	t_envnode	*node;
	t_envnode	*temp;

	if (!env || !env->head)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		temp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	free(env);
	return (0);
}