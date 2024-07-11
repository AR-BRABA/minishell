#include "../includes/minishell.h"

void	print_split(char **array)
{
	int	i = 0;

	while (array[i] != NULL)
	{
		printf("%d: <%s>\n", i, array[i]);
		i++;
	}
}
