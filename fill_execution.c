/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:32:39 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/22 17:43:09 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	between_pipe(t_parser *lst)
{
	int		length;

	if (!lst)
		return (0);
	length = 1;
	while (lst)
	{
		if (lst->type == PIPE)
			length++;
		lst = lst->next;
	}
	return (length);
}

void	count_len(t_parser *lst, int *commands_len, int *redirection_len)
{
	t_parser	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp && (tmp->type == LESS || tmp->type == GREATER \
			|| tmp->type == LESSLESS || tmp->type == GREATERGREATER))
		{
			*redirection_len += 2;
			tmp = tmp->next->next;
			continue ;
		}
		else if (tmp->type == COMMAND)
		{
			if (tmp->stat == GENERAL && !ft_strlen(tmp->token))
			{
				tmp = tmp->next;
				continue ;
			}
			(*commands_len)++;
			tmp = tmp->next;
		}
	}
}

void	init_counters(int *index, int *count)
{
	index[0] = 0;
	index[1] = 0;
	count[0] = 0;
	count[1] = 0;
}

void	handle_word_token(t_parser *tmp, t_execution *new, int *i)
{
	char	**s;
	int		j;

	j = 0;
	s = NULL;
	if (ft_strchr(tmp->token, ' ') && tmp->stat == GENERAL)
	{
		s = ft_split(tmp->token, ' ');
		while (s && s[j])
			new->cmd[(*i)++] = ft_strdup(s[j++]);
	}
	else
		new->cmd[(*i)++] = ft_strdup(tmp->token);
}

void	handle_non_word_token(t_parser **tmp, t_execution *new, int *j)
{
	new->red[(*j)++] = ft_strdup((*tmp)->token);
	new->red[(*j)++] = ft_strdup((*tmp)->next->token);
	*tmp = (*tmp)->next;
}

void	fill_exec_process(t_parser **tmp, int *index, t_execution **new)
{
	while (*tmp && (*tmp)->type != PIPE)
	{
		if (*tmp && (*tmp)->stat == GENERAL && ft_strlen((*tmp)->token) == 0)
			*tmp = (*tmp)->next;
		else
		{
			if ((*tmp)->type == COMMAND)
				handle_word_token(*tmp, *new, &index[0]);
			else
				handle_non_word_token(tmp, *new, &index[1]);
			*tmp = (*tmp)->next;
		}
	}
}

void	send_to_execution(t_parser *token, t_execution **cmd)
{
	t_execution		*new;
	t_parser	*tmp;
	int			index[2];
	int			count[2];

	tmp = token;
	while (tmp)
	{
		init_counters(index, count);
		count_len(tmp, &count[0], &count[1]);
		if (ft_strchr(tmp->token, ' ') && tmp->stat == GENERAL)
			count[0] = ft_split_len(ft_split(tmp->token, ' '));
		new = new_cmd(count[0], count[1], tmp->stat, ft_strlen(tmp->token));
		fill_exec_process(&tmp, index, &new);
		append_to_exec(cmd, new);
		if (tmp && tmp->next)
			tmp = tmp->next;
	}
}
