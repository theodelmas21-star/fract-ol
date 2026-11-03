NAME = fractol
CC = cc
MY_SOURCES = fractol.c \
            create_image.c \
            mandelbrot.c \
            movement.c \
            julia.c
MY_OBJECTS = $(MY_SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3
MLX_DIR = mlx
MLX_INC = -I$(MLX_DIR)
MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

all: $(NAME)

# Initialise le submodule MLX si le dossier est vide
$(MLX_DIR)/Makefile:
	@if [ ! -f $(MLX_DIR)/Makefile ]; then \
		echo "MLX submodule is empty. Initializing..."; \
		git submodule update --init --recursive; \
	fi

# Compile la MLX
$(MLX_DIR)/libmlx_Linux.a: $(MLX_DIR)/Makefile
	@echo "Compiling MLX..."
	@make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(NAME): $(MLX_DIR)/libmlx_Linux.a $(MY_OBJECTS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(MLX_LIB) -o $(NAME)
	@echo " $(NAME) created successfully!"

clean:
	@echo "Cleaning object files..."
	@rm -f $(MY_OBJECTS)
	@make -C $(MLX_DIR) clean 2>/dev/null || true

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re