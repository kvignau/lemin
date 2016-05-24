# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvignau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 10:52:32 by kvignau           #+#    #+#              #
#    Updated: 2016/05/24 11:32:00 by kvignau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

SRC = lemin.c action_lst.c reso.c lstchemin.c check_chemin.c parsing_pipe.c
SRC += parsing_room.c ant.c move_ant.c parsing.c lstchemin_del.c parsing_ant.c
SRC += room_pipe.c test_display_ant.c ajout_dispo.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ft_printf/ all
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L ft_printf/ -lftprintf

clean:
	make -C ft_printf/ clean
	rm -f $(OBJ)

fclean: clean
	make -C ft_printf/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
