NAME = cub3d_proto

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Imlx

SRCS = \
	src/main.c \
	src/init.c \
	src/render.c \
	src/raycast.c \
	src/input.c \
	src/map.c \
	src/cleanup.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
