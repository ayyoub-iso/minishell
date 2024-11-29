#include "../minishell.h"

int exit_status(int _sts, int set)
{
    static int  sts;

    if (set)
        sts = _sts;
    return (sts);
}
