# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 18:30:09 by gtome-ve          #+#    #+#              #
#    Updated: 2025/08/19 20:05:13 by gtome-ve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -Llib -lmlx -lXext -lX11 -lm
INCLUDE = -I./lib/libft -I./lib

SRCS = src/main.c src/map.c src/utils.c src/map_validate.c src/path_check.c src/render.c src/events.c src/map_utils.c src/file_utils.c
OBJS = $(SRCS:.c=.o)

LIBFT = ./lib/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./lib/libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(INCLUDE) -o $(NAME) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ./lib/libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
