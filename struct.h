/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:42:22 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/29 16:42:02 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


typedef struct s_parser t_parser;
typedef struct s_minishell t_minishell;
typedef enum e_stat t_stat;
typedef enum e_type t_type;
typedef struct s_env t_env;
typedef struct s_execution t_execution;

typedef struct s_use
{
	int		len;
	int		start;
	int		end;
	char	*str;
}	t_use;

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
    char *token;// for expansion;
    char *arg; 
    t_type type;
    t_stat stat;
    struct s_parser *next;
};

struct s_env
{
    char *key;
    char *value;
    bool hidden;
    struct s_env *next;
};

struct s_minishell
{
    t_parser *parser;
    char     **env;
    char *line;
    int ret_value;
    int count;
    int exit_status;
    int p_count;
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

typedef struct s_exec
{
    char    *cmd;
    char    **opt;
    int     fd_out;
    int     fd_in;
    bool    run_it;
    struct s_exec   *next;
}   t_exec;

typedef struct s_expand
{
    int start;
    int end;
    char *key;
    char *value;
    char tmp;
    
} t_expand;

typedef enum    s_call
{
    INIT,
    NEW,
    ADD,
    CHANGE,
    SEARCH,
    REMOVE,
    PRINT_XPRT,
    GET_STRCT,
    GET_CHAR
}   t_call;
