NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = minilibx-linux
INCS = -Iinc -I$(MLX)
LDFLAGS = -L$(MLX) -lmlx_Linux -lXext -lX11 -lm -lz

SRCS = src/main.c src/map_parse.c src/map_parse_utils.c src/map_validate.c \
       src/map_validate_utils.c src/map_walls.c src/path_check.c \
       src/path_check_utils.c src/game.c src/game_utils.c src/game_init.c \
       src/game_events.c src/game_hooks.c src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MLX)/libmlx.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(MLX)/libmlx.a:
	@$(MAKE) -C $(MLX)

src/%.o: src/%.c inc/so_long.h
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(MLX) clean 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
