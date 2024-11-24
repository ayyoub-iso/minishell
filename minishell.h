/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:02 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/22 17:37:38 by akharfat         ###   ########.fr       */
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