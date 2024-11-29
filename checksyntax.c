/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksyntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:01 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/29 17:02:25 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_skip_quotes(char *str, int *i)
{
    char quote = str[*i];
    (*i)++;
    while(str[*i] && str[*i] != quote)
        (*i)++;
}

int ft_check_quotes(char *str)
{
    int i = 0;

    while(str[i])
    {
        if(str[i] == 34 || str[i] == 39)
        {
            ft_skip_quotes(str, &i);
            if(str[i] == 0)
                return (1);
        }
        i++;
    }
    return (0);
}
int ft_check_easyrules(char *str)
{
    int i = 0;
    size_t len = 0;
    len = ft_strlen(str);

    if (str[0] == '|' || str[len - 1] == '|')
        return(1);
    while(str[i])
    {
        if (str[i] == '<' && str[i + 1 ] == '<' && str[i + 2] == '<')
            return (1);
        if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
            return (1);
            i++;
    }
    return(0);
}
size_t  ft_number_operator(char *str)
{
    int i = 0;
    size_t count = 0;

    while(str[i])
    {
        if (str[i] == 34 || str[i] == 39)
           ft_skip_quotes(str, &i);
        else if (str[i] == '|')
            count++;
        else if (str[i] == '<' && str[i + 1] != '<')
            count++;
        else if (str[i] == '>' && str[i + 1] != '>')
            count++;
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            i++;
            count++;
        }
        else if (str[i] == '>' && str[i + 1] == '>')
        {
            i++;
            count++;
        }
        i++;
    }
    printf("count = %zu\n", count);
    return(count * 2);
}

void    ft_skip_and_full(char *str, char *newstr, int *i , int *j)
{
    char quote = str[*i];
    newstr[(*j)++] = str[(*i)++];
    while(str[*i] || str[*i] == quote)
        {
            newstr[(*j)++] = str[(*i)++];
        }
   if (str[*i] == quote)
    {
        newstr[(*j)++] = str[(*i)++];
    }   
}

char *ft_edit_input(char *str)
{
    size_t len = ft_strlen(str);
    size_t len2 = ft_number_operator(str) + len;
    printf("len2 == %zu\n", len2);
    char *new_str = malloc(sizeof(char) * (len2 + 1));
    if (!new_str)
        return (NULL);

    int i = 0, j = 0;
    while(str[i])
    {
        if (str[i] == 34 || str[i] == 39)
            ft_skip_and_full(str,new_str,&i,&j);
        else if (str[i] == '<' && str[i + 1] == '<')
        {
            new_str[j++] = ' ';
            new_str[j++] = '<';
            new_str[j++] = '<';
            new_str[j++] = ' ';
            i++;
        }
        else if (str[i] == '>' && str[i + 1] == '>')
        {
            new_str[j++] = ' ';
            new_str[j++] = '>';
            new_str[j++] = '>';
            new_str[j++] = ' ';
            i++;
        }
        else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
        {
            new_str[j++] = ' ';
            new_str[j++] = str[i];
            new_str[j++] = ' ';
        }
        else
            new_str[j++] = str[i];
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}

int ft_count_words(char *str)
{
    int cntword = 0;
    int i = 0;
    while(str[i])
    {
        while(str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (str[i])
        {
            cntword++;
            while(str[i] && str[i] != ' ' && str[i] != '\t')
            {
                if (str[i] == 34 || str[i] == 39)
                {
                    ft_skip_quotes(str, &i);
                }
                if(str[i] != '\0')
                    i++;
            }
        }
        i++;
    }
    return(cntword);
}
char    *my_substr(char *str, int *i)
{
    int start;
    start = 0;

    start = *i;
    while(str[*i] && str[*i] != ' ' && str[*i] != '\t')
    {
        if (str[*i] == 34 || str[*i] == 39)
           ft_skip_quotes(str, i);
        if(str[*i] != '\0')
            (*i)++;
    }
    //int end = *i;
    // printf("end = %d\n", end);
    // printf("start = %d\n", start);
    int len = *i - start;
    //printf("len == %d\n", len);
    char *new_str = malloc(sizeof(char) * len + 1);
    if (!new_str)
        return (NULL);
    int j = 0;
    while(start < *i)
    {
        new_str[j] = str[start];
        start++;
        j++;
    }
    new_str[j] = '\0';
    return(new_str);
}

char **my_split(char *str)
{
    char **array;
    array = NULL;
    int count = 0;
    count = ft_count_words(str);
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);
    int i = 0;
    int j = 0;
    while(str[i])
    {
        while(str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (str[i] != '\0')
        {
            printf("i = %d\n", i);
            array[j] = my_substr(str, &i);
            printf("array[j] == [%s]\n", array[j]);
            j++;
        }
        i++;
    }
    array[j] = NULL;
    return(array);
}
int ft_check_if_quoted(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (str[i] == 34)
            return (0);
        if (str[i] == 39)
            return (1);
        i++;
    }
    return (-1);
}

void    ft_check_type(t_parser *tmp)
{
    if (ft_strcmp(tmp->token, "|") == 0)
       {
            tmp->type = PIPE;
            tmp->stat = GENERAL;
       }
    else if (ft_strcmp(tmp->token, ">") == 0)
        {
            tmp->type = GREATER;
            tmp->stat = GENERAL;
        }
    else if (ft_strcmp(tmp->token, ">>") == 0)
        {
            tmp->type = GREATERGREATER;
            tmp->stat = GENERAL;
        }
    else if (ft_strcmp(tmp->token, "<") == 0)
        {
            tmp->type = LESS;
            tmp->stat = GENERAL;
        }
    else if (ft_strcmp(tmp->token, "<<") == 0)
       {
        tmp->type = LESSLESS;
        tmp->stat = GENERAL;
       }
    else if (ft_check_if_quoted(tmp->token) == 0)
        tmp->stat = INDOUBLEQUOTES;

    else if (ft_check_if_quoted(tmp->token) == 1)
        tmp->stat = INQUOTES;
    else
    {
        tmp->stat = GENERAL;
        tmp->type = COMMAND;
    }
}

void	ft_lstaddback(t_parser **alst, t_parser *new)
{
	t_parser *ptr;

	if (alst && *alst)
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	else if (alst)
		*alst = new;
}

 void   full_my_link_list(char **array, t_parser **parser)
 {
        int i = 0;
        int flag = 0;
        t_parser *tmp;
        tmp = *parser;

        while(array[i])
        {
            tmp = malloc(sizeof(t_parser));
            if (!tmp)
                return;
            if (flag == 1)
            {
                tmp->token = ft_expend_herdoc(array[i]);
                flag = 0;
            }
            else
               tmp->token = ft_expend(array[i]);
            if (!ft_strcmp(array[i], "<<"))
                    flag = 1;
            tmp->arg = array[i];
            ft_check_type(tmp);
            tmp->next = NULL; 
            ft_lstaddback(parser, tmp);
            tmp = tmp->next;
            i++;
        }
}

int check_syntax(char *input, t_parser *parser)
{
    char *newline;
    char **array;

    parser = NULL;
    newline = NULL;
    
    if (ft_check_quotes(input) == 1)
    {
        printf("minishell: syntax error\n");
        return  (1);
    }
    if (ft_check_easyrules(input) == 1)
    {
        printf("minishell: heredoc error\n");
        return (1);
    }    
    newline = ft_edit_input(input);
    array = my_split(newline);
    if (!array)
        return(1);
    full_my_link_list(array, &parser);
    return (0);
}