NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
INCS = -Iinc -I$(MLX_DIR)
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/map_parse.c $(SRC_DIR)/map_parse_utils.c \
       $(SRC_DIR)/map_validate.c $(SRC_DIR)/map_validate_utils.c \
       $(SRC_DIR)/map_walls.c $(SRC_DIR)/path_check.c \
       $(SRC_DIR)/path_check_utils.c $(SRC_DIR)/game.c $(SRC_DIR)/game_utils.c \
       $(SRC_DIR)/game_init.c $(SRC_DIR)/game_events.c $(SRC_DIR)/game_hooks.c \
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:.c=.o)
DEPS = inc/so_long.h

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(MLX_LDFLAGS) -o $@
	@echo "Built $(NAME)"

$(MLX_LIB):
	@if [ ! -f $(MLX_LIB) ]; then cd $(MLX_DIR) && ./configure && make -f makefile.gen 2>/dev/null || true; fi

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@if [ -d $(MLX_DIR) ]; then $(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true; fi
	@echo "clean"

fclean: clean
	@$(RM) $(NAME)
	@echo "fclean"
re: fclean all

.PHONY: all clean fclean re
