/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:50:02 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/26 21:18:33 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_parser *parser(char *line, t_stat stat, t_type type)
// {
//     t_parser *parser;

//     parser = malloc(sizeof(t_parser));
//     parser->token = line;
// 	parser->type = type;
// 	parser->stat = stat;
// 	parser->next = NULL;
//     return (parser);
// }

// void add_parser(t_parser **parser, t_parser *new)
// {
//     t_parser *tmp;
// 	if (!parser || !new)
// 		return;
// 	if (!*parser)
// 	{
// 		*parser = new;
// 		return;
// 	}
// 	tmp = *parser;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }
#include "minishell.h"

t_parser *parser(char *line, t_stat stat, t_type type)
{
    t_parser *new_parser;
    char *new_token;

    if (!line)
        return (NULL);

    new_parser = malloc(sizeof(t_parser));
    if (!new_parser)
        return (NULL);

    // Create a copy of the token
    new_token = ft_strdup(line);
    if (!new_token)
    {
        free(new_parser);
        return (NULL);
    }

    // Initialize the node
    new_parser->token = new_token;
    new_parser->type = type;
    new_parser->stat = stat;
    new_parser->next = NULL;

    return (new_parser);
}

void add_parser(t_parser **parser, t_parser *new)
{
    t_parser *tmp;

    if (!parser || !new)
        return;

    // If list is empty, make new node the head
    if (!*parser)
    {
        *parser = new;
        return;
    }

    // Add to end of list
    tmp = *parser;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

