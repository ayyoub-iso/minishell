#include "../minishell.h"

int check_nl(char **args, int *i, bool *nl)
{
    int j;

    while (args[*i])
    {
        j = 0;
        if (args[*i][j] == '-' && ++j)
        {
            if (!args[*i][j])
                break ;
            while (args[*i][j] == 'n' && args[*i][j])
                j++;
            if (!args[*i][j])
                *nl = false;
            else
                break ;
        }
        else
            break;
        (*i)++;
    }
    return (1);
}

int echo(t_exec *node, int fd)
{
    char    **args;
    bool    nl;
    int     i;

    (1) && (args = node->opt, nl = true, i = 1);
    if (!args[1])
        return (ft_putstr_fd("\n", fd), 1);
    check_nl(args, &i, &nl);
    while (args[i])
    {
        ft_putstr_fd(args[i], fd);
        if (args[i + 1])
            ft_putstr_fd(" ", fd);
        else if (!args[i + 1] && nl)
            ft_putstr_fd("\n", fd);
        i++;
    }
    return (1);
}
