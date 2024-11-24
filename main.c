/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:39 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/24 20:08:35 by akharfat         ###   ########.fr       */
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
    t_env   *envr;
    int lexer_status;
    int heredoc_status;

    minishell = malloc(sizeof(t_minishell));
    if (!minishell)
        return (1);
    parser = NULL;
    envr = NULL;
    store_env(env, &envr);
    minishell->env = env;
    minishell->envriment = envr;
    minishell->ret_value = 0;

    while (1)
    {
        minishell->line = readline("minishell$ ");
        if (!minishell->line)
            break;

        if (minishell->line[0] != '\0')
        {
            add_history(minishell->line);
            lexer_status = lexer(minishell->line, &parser, minishell);
            if (lexer_status == 0)
            {
                heredoc_status = process_heredocs(parser);
                if (heredoc_status == 0)
                {
                }
                else
                {
                    printf("minishell: heredoc error\n");
                    minishell->ret_value = 1;
                }
            }
            else
            {
                printf("minishell: syntax error\n");
                minishell->ret_value = 2;
            }
            cleanup_parser(&parser);
        }
        free(minishell->line);
    }
    free(minishell);
    return (0);
}

char	*get_value(t_minishell **mini, char *key)
{
	t_env	*envr;

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

void	process_dollar_question(char *token, int *i, \
	char **join_it, t_minishell *mini)
{
	char	*str;

	if (token[*i] == '$' && token[*i + 1] == '?')
	{
		str = ft_itoa(mini->ret_value);
		*join_it = ft_strjoin(*join_it, str);
		(*i)++;
	}
}

void	process_dollar_dollar(char *token, int *i, t_minishell **mini)
{
	int	nbr;

	nbr = 0;
	while (token[*i] == '$' && token[*i + 1] == '$')
	{
		(*i)++;
		nbr++;
	}
	(*mini)->count = nbr;
}

void	process_dollar_var(char *token, int *i, \
	char **join_it, t_minishell **mini)
{
	char	*str;
	int		j;

	if ((*mini)->count % 2 == 0)
	{
		(*i)++;
		j = *i;
		while (ft_isalnum(token[*i]) || token[*i] == '_'\
			|| ft_isalpha(token[*i]))
			(*i)++;
		str = get_value(mini, ft_substr(token, j, *i));
		*join_it = ft_strjoin(*join_it, str);
	}
}

void	process_dollar(char *token, int *i, \
	char **join_it, t_minishell *mini)
{
	mini->count = 0;
	process_dollar_question(token, i, join_it, mini);
	process_dollar_dollar(token, i, &mini);
	process_dollar_var(token, i, join_it, &mini);
}

void	process_non_dollar(char *token, int *i, char **join_it)
{
	char	*str;
	int		j;

	j = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	str = ft_substr(token, j, *i);
	*join_it = ft_strjoin(*join_it, str);
}

char	*expansion(char *token, t_minishell *mini)
{
	char	*join_it;
	int		i;

	i = 0;
	join_it = NULL;
	while (token[i])
	{
		if (token[i] == '$')
			process_dollar(token, &i, &join_it, mini);
		else
			process_non_dollar(token, &i, &join_it);
	}
	if (join_it)
		token = ft_strdup(join_it);
	return (token);
}

// void    expanding(char *token, t_minishell *mini)
// {
// 	char *str;
// 	int i;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '"' || token[i] == '\'')
// 		{
// 			int j = i;
// 			i++;
// 			while (token[i] && token[i] != token[j])
// 				i++;
// 			str = ft_substr(token, j, i);
// 			token = ft_strjoin(token, str);
// 			if (token[i] == '\'')
// 				i++;
// 		}
// 		// $
// 		// value
// 		if (token[i] == '$')
// 		{
// 			if (token[i + 1] == '?')
// 			{
// 				str = ft_itoa(mini->ret_value);
// 				token = ft_strjoin(token, str);
// 				i++;
// 			}
// 			else if (token[i + 1] == '$')
// 			{
// 				token = ft_strjoin(token, ft_itoa(getpid()));
// 				i++;
// 			}
// 			else
// 			{
// 				i++;
// 				int j = i;
// 				while (ft_isalnum(token[i]) || token[i] == '_' || ft_isalpha(token[i]))
// 					i++;
// 				str = get_value(&mini, ft_substr(token, j, i));
// 				token = ft_strjoin(token, str);
// 			}
// 		}
// 		else
// 		{
// 			int j = i;
// 			while (token[i] && token[i] != '$')
// 				i++;
// 			str = ft_substr(token, j, i);
// 			token = ft_strjoin(token, str);
// 		}
// 	}
// 	{
// 		/* code */
// 	}
	
// 	return str;
// }