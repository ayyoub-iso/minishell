#include "minishell.h"

char    *get_till_char(char *str, char c)
{
    int     i;
    int     len;
    char    *ret;

    (1) && (len = -1, i = -1);
    while (str[++len] && str[len] != c)
        ;
    ret = malloc(len + 1);
    if (!ret)
        return (NULL);
    while (++i < len)
        ret[i] = str[i];
    ret[i] = '\0';
    return (ret);
}
