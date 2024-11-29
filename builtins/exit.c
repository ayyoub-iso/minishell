#include "../minishell.h"

long    check_over(char *s, bool *ovr)
{
    int     i;
    long    res;
    long    tmp;
    long    sn;

    (1) && (i = 0, sn = 1, res = 0);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
        i++;
    if (s[i] == '-' || s[i] == '+')
        (1) && ((s[i] == '-') && (sn = -1), i++);
    while (s[i] && s[i] >= '0' && s[i] <= '9')
    {
        tmp = res;
        res = (res * 10) + (s[i] - '0');
        if (tmp != res / 10)
            return (*ovr = true, -1);
        i++;
    }
    return (res * sn);
}

int err_msg(char *n, int msg)
{
    if (msg == 1)
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(n, 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(255);
    }
    else if (msg == 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit_status(1, 1);
    }
    return (0);
}

bool    checkArg(char *s)
{
    int i;

    i = 0;
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
        i++;
    if (s[i] == '-' || s[i] == '+')
        i++;
    while (s[i] && s[i] >= '0' && s[i] <= '9')
        i++;
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
        i++;
    if (s[i] != '\0')
        return (false);
    return (true);
}

int My_exit(t_exec *node)
{
    char    **args;
    long    ext;
    bool    ovr;

    (1) && (args = node->opt, ovr = false);
    if (!args[1])
        exit(exit_status(0, 0));
    if (!checkArg(args[1]))
        return (err_msg(args[1], 1));
    else if (args[2])
        return (err_msg(args[1], 2));
    ext = check_over(args[1], &ovr);
    if (ovr)
        return (err_msg(args[1], 1));
    return (exit((char)ext), 1);
}
