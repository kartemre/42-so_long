# =========================
# so_long — 42 (Linux/MLX)
# =========================

NAME    := so_long

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
MLX_DIR := minilibx-linux
INCS    := -I. -I$(MLX_DIR)

# MinilibX (Linux) static lib
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a
MLX_LDFLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

SRCS := \
	step1_main.c \
	step2_map.c \
	step3_validate.c \
	step4_walls.c \
	step5_path.c \
	step6_mlx.c

OBJS := $(SRCS:.c=.o)
DEPS := so_long.h

# -------- Rules --------
all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(MLX_LDFLAGS) -o $@
	@echo "✅ Built $(NAME)"

# Build minilibx once
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# .c -> .o
%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "🧽 clean"

fclean: clean
	@$(RM) $(NAME)
	@echo "🗑️  fclean"

re: fclean all

.PHONY: all clean fclean re
