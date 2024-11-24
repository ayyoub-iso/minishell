/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:30:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/11/16 10:36:43 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_heredoc_filename(void)
{
    static int heredoc_count = 0;
    char *filename;
    char count_str[16];
    
    // Convert count to string
    snprintf(count_str, sizeof(count_str), "%d", heredoc_count++);
    filename = ft_strjoin("/tmp/.heredoc_", count_str);
    return filename;
}

static void handle_sigint_heredoc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130); // Same exit code as bash for SIGINT
}

static int write_heredoc_content(int fd, char *delimiter)
{
    char *line;
    size_t delimiter_len;
    
    delimiter_len = ft_strlen(delimiter);
    signal(SIGINT, handle_sigint_heredoc);
    
    while (1)
    {
        line = readline("> "); // Heredoc prompt
        if (!line)
            break;
            
        // Check if line matches delimiter
        if (ft_strlen(line) == delimiter_len && 
            ft_strncmp(line, delimiter, delimiter_len) == 0)
        {
            free(line);
            break;
        }
        
        // Write line to heredoc file
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    return 0;
}

int handle_heredoc(t_parser *node)
{
    char *filename;
    int fd;
    pid_t pid;
    int status;
    
    if (!node || !node->next || !node->next->token)
        return 1;
        
    filename = get_heredoc_filename();
    if (!filename)
        return 1;
    
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        free(filename);
        return 1;
    }
    
    // Fork to handle heredoc content
    pid = fork();
    if (pid == -1)
    {
        close(fd);
        free(filename);
        return 1;
    }
    
    if (pid == 0)
    {
        // Child process
        write_heredoc_content(fd, node->next->token);
        close(fd);
        exit(0);
    }
    else
    {
        // Parent process
        close(fd);
        waitpid(pid, &status, 0);
        
        // Handle if child was interrupted
        if (WIFSIGNALED(status))
        {
            unlink(filename);
            free(filename);
            return 1;
        }
    }
    
    // Store filename in node for later use
    free(node->token);
    node->token = filename;
    node->type = LESS; // Convert << to < for execution
    
    return 0;
}

// Helper function to process all heredocs in the command line
int process_heredocs(t_parser *parser)
{
    t_parser *current = parser;
    
    while (current)
    {
        if (current->type == LESSLESS)
        {
            if (handle_heredoc(current) != 0)
                return 1;
        }
        current = current->next;
    }
    return 0;
}