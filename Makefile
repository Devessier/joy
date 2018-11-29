# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by dde-jesu          #+#    #+#              #
#    Updated: 2018/11/29 12:02:09 by bdevessi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit
CFLAGS=-Wall -Werror -Wextra -Iincludes
CC=gcc

SRCS = src/main.c src/parser.c \
	   src/solve.c src/reader.c \
	   src/utils.c src/print.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(OBJS): Makefile

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)


.PHONY: clean fclean re proto
