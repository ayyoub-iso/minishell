/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:52:33 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/24 20:18:11 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int is_operator(char c)
// {
//     return (c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t' || c == '\'' || c == '"');
// }

// int lexer(char *input, t_parser **parser)
// {
//     int i;
//     (void)parser;

//     i = 0;
//     while (input[i])
//     {
//         if (input[i] == '\t' || input[i] == ' ')
//             i++;
//         else if (is_operator(input[i]))
//             add_key(input, &i);
//         else
//             add_word(input, &i);
//     }
//     return (0);
// }


// t_parser *add_key (char *input, int *i)
// {
//     char *s;
//     t_parser *node;
//     t_type  type = COMMAND;
    
//     if (input[*i] == '|')
//         type = PIPE;
//     else if (input[*i] == '<')
//     {
//         if (input[*i + 1] == '<')
//         {
//             type = LESSLESS;
//             (*i)++;
//         }
//         else
//             type = LESS;
//     }
//     else if (input[*i] == '>')
//     {
//         if (input[*i + 1] == '>')
//         {
//             type = GREATERGREATER;
//             (*i)++;
//         }
//         else
//             type = GREATER;
//     }
//     else if (input[*i] == '\'')
//         handle_s_quotes(input, i);
//     else if (input[*i] == '"')
//         handle_d_quotes(input, i);
//     s = ft_substr(input, *i, *i + 1);
//     node = parser(s, GENERAL, type);
//     (*i)++;
//     free(s);
//     return (node);
// }

// t_parser *add_word (char *input, int *i)
// {
//     char *s;
//     t_parser *node;
//     int j;

//     j = *i;
//     while(!is_operator(input[j]))
//         (*i)++;
//     s = ft_substr(input, j, *i);
//     node = parser(s, GENERAL, COMMAND);
//     free(s);
//     return (node);
// }

// t_parser *handle_s_quotes(char *input, int *i)
// {
//     char    *s;
//     t_parser    *node;
//     int     j;
//     int     start;

//     j = *i + 1;
//     start = j;
//     while (input[j] && input[j] != '\'')
//         j++;
//     if (!input[j])
//         return (NULL);
//     s = ft_substr(input, start, j - start);
//     node = parser(s, INQUOTES, COMMAND);
//     *i = j;
//     free(s);
//     return (node);
// }

// t_parser *handle_d_quotes(char *input, int *i)
// {
//     char    *s;
//     t_parser    *node;
//     int     j;
//     int     start;

//     j = *i + 1;
//     start = j;
    
//     while (input[j] && input[j] != '"')
//     {
//         if (input[j] == '\\' && input[j] != '"')
//                 j++;
//         j++;        
//     }
//     if (!input[j])
//         return (NULL);

//     s = ft_substr(input, start, j - start);
//     node = parser(s, INDOUBLEQUOTES, COMMAND);
//     *i = j;
//     free(s);
//     return (node);    
// }

/* lexer.c */

/* lexer.c */
// #include "minishell.h"

// /* lexer.c */
// #include "minishell.h"

// static int is_operator(char c)
// {
//     return (c == '|' || c == '>' || c == '<');
// }

// static int is_whitespace(char c)
// {
//     return (c == ' ' || c == '\t');
// }

// static t_parser *handle_word(char *input, int *i)
// {
//     int start;
//     int len;
//     char *token;
//     t_parser *node;

//     start = *i;
//     len = 0;
//     // Count length until whitespace or operator
//     while (input[*i + len] && !is_whitespace(input[*i + len]) && !is_operator(input[*i + len]))
//         len++;
    
//     // Extract the word
//     token = ft_substr(input, start, len);
//     if (!token)
//         return (NULL);
    
//     // Create node with the word
//     node = parser(token, GENERAL, COMMAND);
//     free(token);
    
//     // Update position
//     *i += len;
    
//     return (node);
// }

// static t_parser *handle_operator(char *input, int *i)
// {
//     char *token;
//     t_parser *node;
//     t_type type;
//     int len;

//     len = 1;
//     // Determine operator type
//     if (input[*i] == '|')
//         type = PIPE;
//     else if (input[*i] == '<')
//     {
//         if (input[*i + 1] == '<')
//         {
//             type = LESSLESS;
//             len = 2;
//         }
//         else
//             type = LESS;
//     }
//     else if (input[*i] == '>')
//     {
//         if (input[*i + 1] == '>')
//         {
//             type = GREATERGREATER;
//             len = 2;
//         }
//         else
//             type = GREATER;
//     }
//     else
//         return (NULL);

//     // Extract operator token
//     token = ft_substr(input, *i, len);
//     if (!token)
//         return (NULL);
    
//     // Create node
//     node = parser(token, GENERAL, type);
//     free(token);
    
//     // Update position
//     *i += len;
    
//     return (node);
// }

// int lexer(char *input, t_parser **parser)
// {
//     int i;
//     t_parser *new_node;

//     if (!input || !parser)
//         return (1);

//     // Initialize or clear existing parser
//     *parser = NULL;
    
//     i = 0;
//     while (input[i])
//     {
//         // Skip whitespaces
//         while (input[i] && is_whitespace(input[i]))
//             i++;
            
//         if (!input[i])
//             break;
            
//         // Handle operators
//         if (is_operator(input[i]))
//             new_node = handle_operator(input, &i);
//         else
//             // Handle words
//             new_node = handle_word(input, &i);
            
//         if (!new_node)
//             return (1);
            
//         // Add node to list
//         add_parser(parser, new_node);
//     }
//     return (0);
// }

/* lexer.c */
#include "minishell.h"

static int is_operator(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

static t_parser *handle_quotes(char *input, int *i)
{
    char quote_type;
    int start;
    int len;
    char *token;
    t_parser *node;
    t_stat status;

    quote_type = input[*i];  // Save quote type (' or ")
    start = *i + 1;          // Start after the opening quote
    len = 0;

    // Determine quote type status
    status = (quote_type == '\'') ? INQUOTES : INDOUBLEQUOTES;

    // Find closing quote
    while (input[start + len] && input[start + len] != quote_type)
        len++;

    // If no closing quote found
    if (!input[start + len])
        return (NULL);

    // Extract content between quotes
    token = ft_substr(input, start, len);
    if (!token)
        return (NULL);

    // Create node with proper quote status
    node = parser(token, status, COMMAND);
    free(token);

    // Update position to after closing quote
    *i = start + len + 1;

    return (node);
}

static t_parser *handle_word(char *input, int *i)
{
    int start;
    int len;
    char *token;
    t_parser *node;

    start = *i;
    len = 0;
    while (input[start + len] && !is_whitespace(input[start + len]) && 
           !is_operator(input[start + len]) && input[start + len] != '\'' && 
           input[start + len] != '"')
        len++;

    token = ft_substr(input, start, len);
    if (!token)
        return (NULL);

    node = parser(token, GENERAL, COMMAND);
    free(token);

    *i += len;
    return (node);
}

static t_parser *handle_operator(char *input, int *i)
{
    char *token;
    t_parser *node;
    t_type type;
    int len;

    len = 1;
    if (input[*i] == '|')
        type = PIPE;
    else if (input[*i] == '<')
    {
        if (input[*i + 1] == '<')
        {
            type = LESSLESS;
            len = 2;
        }
        else
            type = LESS;
    }
    else if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            type = GREATERGREATER;
            len = 2;
        }
        else
            type = GREATER;
    }
    else
        return (NULL);

    token = ft_substr(input, *i, len);
    if (!token)
        return (NULL);

    node = parser(token, GENERAL, type);
    free(token);

    *i += len;
    return (node);
}

// int lexer(char *input, t_parser **parser)
// {
//     int i;
//     t_parser *new_node;

//     if (!input || !parser)
//         return (1);

//     *parser = NULL;
//     i = 0;

//     while (input[i])
//     {
//         // Skip whitespaces
//         while (input[i] && is_whitespace(input[i]))
//             i++;

//         if (!input[i])
//             break;

//         // Handle quotes
//         if (input[i] == '\'' || input[i] == '"')
//             new_node = handle_quotes(input, &i);
//         // Handle operators
//         else if (is_operator(input[i]))
//             new_node = handle_operator(input, &i);
//         // Handle regular words
//         else
//             new_node = handle_word(input, &i);

//         if (!new_node)
//             return (1);

//         add_parser(parser, new_node);
//     }
//     return (0);
// }

// void    expanding(t_parser **token, t_minishell *mini)
// {
//     (void)mini;
//     printf("%s\n", (*token)->token);
// }

// static int validate_token_sequence(t_parser *parser, t_minishell *minishell)
// {
//     (void)minishell;
//     t_parser *current = parser;
//     t_type prev_type = COMMAND; // Assume first token is a command

//     while (current)
//     {
//         // Check for invalid sequences
//         if ((prev_type == LESS || prev_type == GREATER || prev_type == LESSLESS || prev_type == GREATERGREATER) && current->type != COMMAND)
//         {
//             printf("minishell: syntax error near unexpected token \n");
//             return 1; // < |, > |, << |, >> | are invalid
//         }
//         if (current->type == PIPE && (prev_type == PIPE || !current->next))
//         {
//             printf("minishell: syntax error near unexpected token \n");
//             return 1; // | at start/end or consecutive pipes are invalid
//         }
//         if (ft_strchr(current->token, '$') && current->stat != INQUOTES)
//             current->token = expansion(current->token, minishell);
//         prev_type = current->type;
//         current = current->next;
//     }

//     return 0; // Valid sequence
// }

// static int validate_token_sequence(t_parser *parser, t_minishell *minishell)
// {
//     (void)minishell;
//     t_parser *current = parser;
//     t_type prev_type = COMMAND;  // Start with NONE instead of COMMAND

//     // Handle pipe at the start of input
//     if (current && current->type == PIPE)
//     {
//         printf("minishell: syntax error near unexpected token `|'\n");
//         return (1);
//     }

//     while (current)
//     {
//         // Handle consecutive pipes
//         if (current->type == PIPE && prev_type == PIPE)
//         {
//             printf("minishell: syntax error near unexpected token `|'\n");
//             return (1);
//         }

//         // Handle pipe at the end of input
//         if (current->type == PIPE && !current->next)
//         {
//             printf("minishell: syntax error near unexpected token `|'\n");
//             return (1);
//         }

//         // Handle redirection operators
//         if ((prev_type == LESS || prev_type == GREATER || 
//              prev_type == LESSLESS || prev_type == GREATERGREATER) 
//             && current->type != COMMAND)
//         {
//             printf("minishell: syntax error near unexpected token `%s'\n", 
//                    current->token);
//             return (1);
//         }

//         // Handle expansion if needed
//         if (ft_strchr(current->token, '$') && current->stat != INQUOTES)
//             current->token = expansion(current->token, minishell);
//         printf("|%s|\n", current->token);
//         prev_type = current->type;
//         current = current->next;
//     }

//     return (0);
// }

static int validate_token_sequence(t_parser *parser, t_minishell *minishell)
{
    (void)minishell;
    t_parser *current = parser;
    t_type prev_type = COMMAND;

    // Handle pipe at the start of input
    if (current && current->type == PIPE)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (1);
    }

    // Handle single redirection at start
    if (current && (current->type == LESS || current->type == GREATER || 
        current->type == LESSLESS || current->type == GREATERGREATER))
    {
        if (!current->next)
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return (1);
        }
    }

    while (current)
    {
        // Handle consecutive pipes
        if (current->type == PIPE && prev_type == PIPE)
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (1);
        }

        // Handle pipe at the end of input
        if (current->type == PIPE && !current->next)
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (1);
        }

        // Handle redirection operators
        if ((prev_type == LESS || prev_type == GREATER || 
             prev_type == LESSLESS || prev_type == GREATERGREATER))
        {
            if (!current || current->type != COMMAND)
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
            }
        }

        // Handle redirection at end of input
        if ((current->type == LESS || current->type == GREATER || 
             current->type == LESSLESS || current->type == GREATERGREATER) 
            && !current->next)
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return (1);
        }

        // Handle expansion if needed
        if (ft_strchr(current->token, '$') && current->stat != INQUOTES)
            current->token = expansion(current->token, minishell);

        prev_type = current->type;
        current = current->next;
    }

    return (0);
}

static void clear_parser_list(t_parser **parser)
{
    t_parser *current;
    t_parser *next;

    if (!parser || !*parser)
        return;

    current = *parser;
    while (current)
    {
        next = current->next;
        free(current->token);
        free(current);
        current = next;
    }

    *parser = NULL;
}

int lexer(char *input, t_parser **parser, t_minishell *mini)
{
    int i;
    t_parser *new_node;
    t_execution *cmd;
    cmd = NULL;

    if (!input || !parser)
        return 1;

    *parser = NULL;
    i = 0;

    while (input[i])
    {
        // Skip whitespaces
        while (input[i] && is_whitespace(input[i]))
            i++;

        if (!input[i])
            break;

        if (input[i] == '\'' || input[i] == '"')
            new_node = handle_quotes(input, &i);
        else if (is_operator(input[i]))
            new_node = handle_operator(input, &i);
        else
            new_node = handle_word(input, &i);

        if (!new_node)
            return 1;

        add_parser(parser, new_node);
    }

    // Validate the token sequence
    if (validate_token_sequence(*parser, mini))
    {
        clear_parser_list(parser);
        return 1;
    }
    send_to_execution(*parser, &cmd);
    return 0;
}