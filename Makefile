# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 11:22:50 by akharfat          #+#    #+#              #
#    Updated: 2024/11/15 11:50:14 by akharfat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	$(shell find . -name "*.c")
NAME	=	minishell
CC		=	cc
HEADER	=	minishell.h struct.h
CFLAGS	=	-Wall -Wextra -Werror
OBJS	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean