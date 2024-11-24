/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:42:22 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/22 17:54:13 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


typedef struct s_parser t_parser;
typedef struct s_minishell t_minishell;
typedef enum e_stat t_stat;
typedef enum e_type t_type;
typedef struct s_env t_env;
typedef struct s_execution t_execution;

enum e_stat
{
    GENERAL,
    INQUOTES,
    INDOUBLEQUOTES,
};

enum    e_type
{
    COMMAND,
    LESS,
    LESSLESS,
    GREATER,
    GREATERGREATER,
    PIPE,
    WHITESPACE,
};

struct s_parser
{
    char *token;
    t_type type;
    t_stat stat;
    struct s_parser *next;
};

struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
};

struct s_minishell
{
    t_parser *parser;
    char **env;
    char *line;
    int ret_value;
    int count;
    t_env   *envriment;
};

struct s_execution
{
    char **cmd;
    char **red;
    t_stat  stat;
    int cmd_len;
    t_execution *next;
};