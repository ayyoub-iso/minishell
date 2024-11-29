/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:02 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/27 12:42:15 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "struct.h"

// typedef struct s_expand
// {
//     int start;
//     int end;
//     char *key;
//     char *value;
//     char tmp;
    
// } t_expand;


void add_parser(t_parser **parser, t_parser *new);
t_parser *parser(char *line, t_stat stat, t_type type);
int lexer(char *input, t_parser **parser, t_minishell *minishell);
// t_parser *add_word (char *input, int *i);
// t_parser *add_key (char *input, int *i);
// t_parser *handle_s_quotes(char *input, int *i);
// t_parser *handle_d_quotes(char *input, int *i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strchr(const char *s, int c);
int	ft_isalnum(int c);
int	ft_strcmp(char *s1, char *s2);

char *expansion(char *token, t_minishell *mini);

int process_heredocs(t_parser *parser);
int handle_heredoc(t_parser *node);
char	*ft_itoa(int n);
int	ft_toupper(int c);
int	ft_isalpha(int c);
t_execution *new_cmd(int cmd, int red, t_stat stat, int len);
void	append_to_exec(t_execution **cmds, t_execution *cmd);
int	store_env(char **envr, t_env **env);
t_env	*new_env(char *key, char *value);
void	append_env(t_env **env, t_env *node);
char	**ft_split(const char *str, char spliter);
void	send_to_execution(t_parser *token, t_execution **cmd);

// exucution
int	exec(t_minishell *msh);
t_exec   *setup_exec_list(t_parser *s, t_minishell *msh);
bool  is_reder(int type);
int   set_fd(t_exec *s, int reder_type, char *file);
char  **get_char_env(char **envv, int set);
int   pipe_count(t_exec *h);
bool    isBuilt(char *cmd);
int exit_status(int _sts, int set);
// signals 
int set_signals(void);
void	sig_hand(int sig);
void	child_sig(int sig);
int     ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// builtins
int builtin_nf(t_exec *node);
int echo(t_exec *node, int fd);
int My_exit(t_exec *node);
char    *get_till_char(char *str, char c);
void    *_env_(char **env, char *key, char *value, t_call call);
void prnt_env(int fd);
int disp_exprt(int fd);
t_env   *add_env(t_env **head, char *key, char *value, t_call call);

//------------ hamza------
int check_syntax(char *input, t_parser *parser);