NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llib -lmlx -lXext -lX11 -lm

SRCS = src/main.c src/map.c src/utils.c src/parse.c src/parse2.c src/render.c src/events.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
