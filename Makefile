NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
MLX_DIR = mlx
LIBFT_DIR = libft
GNL_DIR = get_next_line

SRCS = \
	src/calc_rc.c src/cleanup.c src/delta_time.c \
	src/error.c src/extraction_xpm.c src/gnl_to_map.c \
	src/grid.c src/init.c src/input.c src/main.c \
	src/move_player.c src/movement.c src/parsing_cub.c src/parsing_map.c src/player_position.c\
	src/player.c src/raycast.c src/render.c src/rgb_to_int.c src/util.c \
	src/validation_args.c src/validation_xpm.c src/xpm_color_def.c src/xpm_header.c \
	src/xpm_pixel.c src/xpm_to_image.c init_rc.c\
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c


OBJS = \
	obj/calc_rc.o obj/cleanup.o obj/delta_time.o \
	obj/error.o obj/extraction_xpm.o obj/gnl_to_map.o \
	obj/grid.o obj/init.o obj/input.o obj/main.o \
	obj/move_player.o obj/movement.o obj/parsing_cub.o obj/parsing_map.o obj/player_position.o\
	obj/player.o obj/raycast.o obj/render.o obj/rgb_to_int.o obj/util.o \
	obj/validation_args.o obj/validation_xpm.o obj/xpm_color_def.o obj/xpm_header.o \
	obj/xpm_pixel.o obj/xpm_to_image.o obj/init_rc.o\
	obj/get_next_line.o obj/get_next_line_utils.o

INCLUDES = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: get_next_line/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
