/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:10:18 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/29 15:53:09 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execution *new_cmd(int cmd, int red, t_stat stat, int len)
{
    t_execution	*new;

	new = malloc(sizeof(t_execution));
	new->cmd = malloc(sizeof(char *) * (cmd + 1));
	new->red = malloc(sizeof(char *) * (red + 1));
	new->cmd[cmd] = NULL;
	new->red[red] = NULL;
	new->stat = stat;
	new->cmd_len = len;
	new->next = NULL;
	return (new);
}

void	append_to_exec(t_execution **cmds, t_execution *cmd)
{
	t_execution	*head;

	if (!cmds || !cmd)
		return ;
	if (!*cmds)
	{
		*cmds = cmd;
		return ;
	}
	head = *cmds;
	while (head->next)
		head = head->next;
	head->next = cmd;
}
