/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:39 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/29 16:25:12 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cleanup_parser(t_parser **parser)
{
	t_parser *current;
	t_parser *next;

	if (!parser || !*parser)
		return;

	current = *parser;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
	*parser = NULL;
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_minishell *minishell;
	t_parser *parser;
	t_env *envr;
	// int lexer_status;
	// int heredoc_status;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
	parser = NULL;
	envr = NULL;
	store_env(env, &envr);
	minishell->env = env;
	minishell->envriment = envr;
	minishell->ret_value = 0;
	set_signals();
	while (1)
	{
		minishell->line = readline("minishell$ ");
		if (!minishell->line)
			break;

		if (minishell->line[0] != '\0')
		{
			add_history(minishell->line);
			if(!check_syntax(minishell->line , minishell->parser))
				return(-1);
			exec(minishell);
			cleanup_parser(&parser);
		}
		free(minishell->line);
	}
	free(minishell);
	return (0);
}

char *get_value(t_minishell **mini, char *key)
{
	t_env *envr;

	if (!key)
		return (ft_strdup(""));
	envr = (*mini)->envriment;
	while (envr)
	{
		if (!ft_strcmp(envr->key, key))
		{
			printf("%s\n", envr->value);
			return (envr->value);
		}
		envr = envr->next;
	}
	return (ft_strdup(""));
}

void process_dollar_question(char *token, int *i,
							 char **join_it, t_minishell *mini)
{
	char *str;

	if (token[*i] == '$' && token[*i + 1] == '?')
	{
		str = ft_itoa(mini->ret_value);
		*join_it = ft_strjoin(*join_it, str);
		(*i)++;
	}
}

void process_dollar_dollar(char *token, int *i, t_minishell **mini)
{
	int nbr;

	nbr = 0;
	while (token[*i] == '$' && token[*i + 1] == '$')
	{
		(*i)++;
		nbr++;
	}
	(*mini)->count = nbr;
}

void process_dollar_var(char *token, int *i,
						char **join_it, t_minishell **mini)
{
	char *str;
	int j;

	if ((*mini)->count % 2 == 0)
	{
		(*i)++;
		j = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_' || ft_isalpha(token[*i]))
			(*i)++;
		str = get_value(mini, ft_substr(token, j, *i));
		*join_it = ft_strjoin(*join_it, str);
	}
}

void process_dollar(char *token, int *i,
					char **join_it, t_minishell *mini)
{
	mini->count = 0;
	process_dollar_question(token, i, join_it, mini);
	process_dollar_dollar(token, i, &mini);
	process_dollar_var(token, i, join_it, &mini);
}

void process_non_dollar(char *token, int *i, char **join_it)
{
	char *str;
	int j;

	j = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	str = ft_substr(token, j, *i);
	*join_it = ft_strjoin(*join_it, str);
}
char *ft_strrange(char *s, int start, int end);
bool special_letter(char l)
{
	char *s;
	int i;

	i = 0;
	s = "$=/*-+\"\'@!#%^.*:";
	if (l == ' ' || (l >= 9 && l <= 13))
		return (true);
	while (s[i])
	{
		if (s[i] == l)
			return (true);
		i++;
	}
	return (false);
}
char *get_key(char *s)
{
	int start = 0;
	int end = 0;
	int i;
	char *str;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = i++;
			while (s[i] && !special_letter(s[i]))
				i++;
			end = i;
			break;
		}
		i++;
	}
	str = ft_strrange(s, start, end);
	return (str);
}

char *expand_exit_status(int status)
{
	char *str;

	str = ft_itoa(status);
	return (str);
}
char *expanding_valuess(char *key, t_env *env)
{
	t_env *tmp;
	char *value;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			value = ft_strdup(tmp->value);
			return (value);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
bool checkexpanding(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
char *get_not_key(char *s)
{
	int start;
	int end;
	int i;
	char *str;

	end = 0;
	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			break;
		i++;
	}
	str = ft_strrange(s, 0, i - 1);
	printf("str |%s|\n",str);
	return (str);
}
char *expansion(char *s, t_minishell *mini)
{
	int i = 0;
	t_expand e;
	char *buffer = NULL;
	char *tmp;

	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '$' && s[i + 2] == 0)
			{
				buffer = ft_strjoin(buffer, ft_strdup("$"));
				i++;
			}
			else if (s[i + 1] == '?')
			{
				buffer = ft_strjoin(buffer, ft_itoa(1337));
				i++;
			}
			else if (s[i + 1] == '\"' || s[i + 1] == '\'')
				i++;
			else
			{
				e.key = get_key(s + i);
				i += ft_strlen(e.key) - 1;
				tmp = get_value(&mini, e.key + 1);
				buffer = ft_strjoin(buffer, tmp);
			}
		}
		else
		{
			tmp = get_not_key(s + i);
			i += ft_strlen(tmp); 
			buffer = ft_strjoin(buffer, tmp);
		}
		i++;
	}
	return (buffer);
}