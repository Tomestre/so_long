# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtome-ve <gtome-ve@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/17 18:30:09 by gtome-ve          #+#    #+#              #
#    Updated: 2025/08/17 19:42:03 by gtome-ve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llib -lmlx -lXext -lX11 -lm
INCLUDE = -I./lib/libft -I./lib

SRCS = src/main.c src/map.c src/utils.c src/parse.c src/parse2.c src/render.c src/events.c src/map_split.c
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
