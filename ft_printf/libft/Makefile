# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvignau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 10:04:06 by kvignau           #+#    #+#              #
#    Updated: 2016/03/23 19:21:27 by kvignau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = $(shell ls | grep ".c")

SRCO = $(SRC:.c=.o)
HEADERS = .
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

re: fclean all

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(SRCO)
	ar rc $@ $^
	ranlib $@

clean:
	rm -f $(SRCO)

fclean: clean
	rm -f $(NAME)

.PHONY: re clean fclean all
