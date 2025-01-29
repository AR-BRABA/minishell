#include "../../includes/minishell.h"

int	check_n_flag(char **arg)
{
    int	n = 0;

    if (arg && arg[0] && ft_strncmp(arg[0], "-n", 2) == 0)
    {
        n = 2;
        while (arg[0][n] == 'n')
            n++;
        if (n != (int)ft_strlen(arg[0]))
            n = 0;
        else
            n = 1;
    }
    return (n);
}

int	ft_echo(char **arg)
{
    int	n = check_n_flag(arg);
    int	i = n;

    while (arg && arg[i])
    {
        ft_putstr_fd(arg[i++], 1);
        if (arg[i])
            ft_putchar_fd(' ', 1);
    }
    if (!n)
        ft_putchar_fd('\n', 1);
    return (0);
}