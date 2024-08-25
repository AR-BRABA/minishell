#include "../../includes/minishell.h"
/*
int	cmdlen(char **input)
{
	int	i = 0;

	while (input[i] != NULL && input[i][0] != '|')
		i++;
	if (input[i] != NULL && input[i][0] == '|')
		i++;
	return(i);
}

enum e_type {
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_FILE,
	APPEND,
	HEREDOC,
};

typedef struct	s_node {
	char	*value;
	int	type;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct	s_list {
	int	len;
	t_node	*head;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct	s_tab {
	t_list	*head;
	int	len;
}	t_tab;

void	add_node(t_node *new, t_list *list)
{
	int	count = 0;
	t_node	*node;
	
	node = list->head;
	if (!node)
		list->head = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
		new->prev = node;
	}
}

void	add_list(t_list *new, t_tab *cmdtable)
{
	int	count = 0;
	t_list	*list;
	
	list = cmdtable->head;
	if (!list)
		cmdtable->head = new;
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = new;
		new->prev = list;
	}
}

t_node	*new_node(char *token)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	cmd->value = token; //dup??
	cmd->type = -1;
	cmd->prev = NULL;
	cmd->next = NULL;

	return (cmd);
}

t_list	*new_list(char **input)
{
	int	i = 0;
	t_node	*cmd;
	t_list	*cmdlist;

	cmdlist = malloc(sizeof(t_list));
	cmdlist->len = 0;
	cmdlist->prev = NULL;
	cmdlist->next = NULL;
	while (input[i] != NULL)
	{
		cmd = new_node(input[i]);
		add_node(cmd, cmdlist);
		cmdlist->len++;
		if (input[i] && input[i][0] == '|')
			break ;
		i++;
	}
	return (cmdlist);
}

void	get_type(t_node *token)
{
	if (token->prev == NULL || token->prev->value[0] == '|')
		token->type = COMMAND;
	else if (token->value[0] == '|')
		token->type = PIPE;
	else if (token->value[0] == '<' || token->value[0] == '>')
	{
		if (token->value[0] == '<' && token->value[1] == '<')
			token->type = HEREDOC; //delimitador!!
		else if (token->value[0] == '>' && token->value[1] == '>')
			token->type = APPEND;
		else if (token->value[0] == '<' && token->value[1] == '\0')
			token->type = REDIRECT_IN;
		else if (token->value[0] == '>' && token->value[1] == '\0')
			token->type = REDIRECT_OUT;
		token->next->type = REDIRECT_FILE;
	}
	else
		token->type = ARG;
}

void	identify_tokens(t_tab *cmdtable)
{
	int	index = 0;
	t_list	*cmdline;
	t_node	*token;
	
	cmdline = cmdtable->head;
	token = cmdline->head;
	while (cmdline != NULL && token != NULL)
	{
		if (token->type == -1)
			get_type(token);
		// if (token->type <= FD)
		// {
		// 	expand_var(token->value);
		// 	remove_quote(token->value);
		// }
		// em outra func
		token = token->next;
		if (token == NULL)
		{
			cmdline = cmdline->next;
			if (cmdline == NULL)
				break ;
			token = cmdline->head;
		}
	}
}

t_tab	*get_cmdtable(char **input)
{
	int	i = 0;
	int	cmd = 0;
	t_list	*list;
	t_tab	*cmdtable;

	list = new_list(&input[i]);
	cmdtable = malloc(sizeof(t_tab));
	cmdtable->head = list;
	cmdtable->len = 1;
	list = list->next;
	i += cmdlen(&input[i]);
	while (input[i] != NULL)
	{
		list = new_list(&input[i]);
		add_list(list, cmdtable);
		i += cmdlen(&input[i]);
		cmdtable->len++;
	}
	identify_tokens(cmdtable);
	// format(cmdtable);
	return (cmdtable);
}

void	print_list(t_list *list)
{
	t_node	*node;

	node = list->head;
	if(!node)
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
	printf("NULL");
}

void	print_tab(t_tab	*table)
{
	t_list	*list;
	int	size;
	int	count;

	if(!table)
	{
		printf("No tabLe!!\n");
		return ;
	}
	list = table->head;
	if(!list)
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
*/
typedef struct	s_envnode {
	char	*key;
	char	*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
} t_envnode;

typedef struct	s_env {
	int	len;
	t_envnode	*head;
	t_envnode	*tail;
} t_env;

t_envnode	*new_envnode(char *envp)
{
	char	**split;
	t_envnode	*node;
	
	split = ft_split(envp, '=');
	node = malloc(sizeof(t_envnode));
	node->key = split[0];
	node->value = split[1];
	node->prev = NULL;
	node->next = NULL;
	free(split);
	return (node);
}

void	addback_env(t_envnode *new, t_env *list)
{
	t_envnode	*node;

	node = list->head;
	if (!node)
	{
		list->head = new;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	new->prev = node;
	node->next = new;
	list->len++;
}

t_env	*get_env_list(char **envp)
{
	int	i = 0;
	t_env	*env;
	t_envnode	*node;

	if (!envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->len = 0;
	env->head = NULL;
	env->tail = env->head;
	while (envp[i] != NULL)
	{
		node = new_envnode(envp[i]);
		addback_env(node, env);
		i++;
	}
	env->tail = node;
	return (env);
}

//TODO: test
// void	destroy_table(t_tab *cmdtable)
// {
// 	int	index = 0;
// 	t_list	*cmdline;
// 	t_list	*keepline;
// 	t_node	*token;
// 	t_node	*keeptoken;
// 	
// 	cmdline = cmdtable->head;
// 	token = cmdline->head;
// 	while (cmdline != NULL && token != NULL)
// 	{
// 		keeptoken = token->next;
// 		free(token);
// 		if (keeptoken == NULL)
// 		{
// 			keepline = cmdline->next;
// 			free(cmdline);
// 			if (keepline == NULL)
// 				break ;
// 			cmdline = keepline;
// 			token = keepline->head;
// 		}
// 		else
// 			token = keeptoken;
// 	}
// 	free(cmdtable);
// }

// essa func eh o builtin do env, mudar a formatacao pra ficar igual ao env
void	print_env(t_env	*env)
{
	t_envnode	*node;
	
	if (!env)
	{
		printf("no env!!");
		return;
	}
	printf("total env = %i\n", env->len);
	node = env->head;
	while (node != NULL)
	{
		printf("key: %s            value: %s\n", node->key, node->value);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	// char	**input;
	// t_tab	*cmdtable;
	//
	// print_split(envp);
	// exit(1);
	// input = metachar_split(argv[1]);
	// print_split(input);
	// cmdtable = get_cmdtable(input);
	// print_tab(cmdtable);
	// free(input);
	//
	(void)argc;
	(void)argv;
	t_env	*env;

	env = get_env_list(envp);
	print_env(env);
	return(0);
}
//todo: void destroy_table()
//frees!
//protect malloc
//
// cc -Wall -Wextra includes/libft/ft_strlen.c srcs/parser/command_table.c srcs/parser/free.c srcs/parser/identify_char.c srcs/parser/tokenizer.c srcs/parser/tokenizer_utils.c srcs/parser/print.c -ggdb3
//oi oi a | grep x
//
//fazer env antes de ampliar var
/*
int	count_varlen(char *token)
{

}

char	*get_key(char *token)
{
	int	i = 0;

	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			i++;
			
		}
	}
}

char	*get_key_value(char *token)
{

}

int	expanded_strlen(char *token)
{
	int	squote = 2;
	int	varlen = 0;
	int	i = 0;

	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			//pegar key pra achar var (usar a outra func de molde)
			varlen += count_varlen(&token[i]);
			while (token[i] && token[i] != ' ') //enquanto for key -eh key ate o final ou espaco?
				i++;
		}
		i++;
	}
	return (varlen + i);
}

void	expand_var(char *token)
{
	int	squote = 2;
	int	i = 0;
	int	count;
	char	*key;
	char	*newval;

	newval = malloc((expanded_strlen(token) + 1) * sizeof(char));
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			squote++;
		else if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' && squote % 2 == 0)
		{
			key = get_key(&token[i]);
			ft_strcat(newval[count], get_key_value(key));
			while (*key++)
				i++;
		}
		newval[count++] = token[i++];
	}
	free(token); //tem q dar o free no char ** -- mudar isso, fazer 1 dup
	token = newval;
}

void	remove_quote(t_node *token)
{
	int	i = 0;
	int	squote = 0;
	int	dquote = 0;

	while ()

}
*/
