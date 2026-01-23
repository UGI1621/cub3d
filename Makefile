
NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror
# CFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
MLX_DIR = mlx
LIBFT_DIR = libft
GNL_DIR = get_next_line

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(GNL_DIR)/*.c)
# SRCS = \
# 		$(SRC_DIR)/cub3d.c \
# 		$(SRC_DIR)/error.c $(SRC_DIR)/handle_keys.c $(SRC_DIR)/initialization.c \
# 		$(SRC_DIR)/is_reachable.c $(SRC_DIR)/move.c $(SRC_DIR)/painting.c \
# 		$(SRC_DIR)/util.c $(SRC_DIR)/util2.c $(SRC_DIR)/validation_args.c $(SRC_DIR)/validation_map.c \
# 		$(GNL_DIR)/get_next_line_utils.c $(GNL_DIR)/get_next_line.c \

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
# MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
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
