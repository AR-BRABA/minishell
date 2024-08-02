#include "../includes/minishell.h"

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

typedef struct	s_table {
	char	**tokens;
	t_node	**frases;
}	t_table;

t_node	*new_node()
{
	
}

t_node	*new_frase()
{
	
}

t_table	*get_cmdtable(char **tokens)
{
	int	tokens = 0;
	int	frases = 0;
	t_node	**frases;
	t_table	*cmdtable;
	
	
	
	return (cmdtable);
}

