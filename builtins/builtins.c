#include "../minishell.h"

bool    isBuilt(char *cmd)
{
    if (!cmd)
        return (false);
    return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
            || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
            || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset")
            || !ft_strcmp(cmd, "exit"));
}

int builtin_nf(t_exec *node)
{
    if (!ft_strcmp(node->cmd, "echo"))
        return (echo(node, node->fd_out));
    else if (!ft_strcmp(node->cmd, "exit"))
        return (My_exit(node));
    else if (!ft_strcmp(node->cmd, "env"))
        return (prnt_env(node->fd_out), 1);
    else if (!ft_strcmp(node->cmd, "export") && !node->opt[1])
        return (disp_exprt(node->fd_out));
    return (1);
}
