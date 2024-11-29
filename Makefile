# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 11:22:50 by akharfat          #+#    #+#              #
#    Updated: 2024/11/27 12:44:59 by akharfat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	build.c builtins/builtins.c builtins/echo.c builtins/exit.c env/env.c execution/exec.c \
			execution/handle_reder.c execution/list.c execution/signals.c execution/utils.c execution_utils.c fill_execution.c \
			ft_expand.c ft_split.c herdoc.c main.c utils.c utils2.c utils3.c utils4.c execution/exit_status.c
NAME	=	minishell
CC		=	cc
HEADER	=	minishell.h struct.h
CFLAGS	=	-Wall -Wextra -Werror
OBJS	=	$(SRC:.c=.o)

READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(READLINE_L) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -I $(READLINE_I) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean