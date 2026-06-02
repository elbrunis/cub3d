NAME = cub3D
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iminilibx-linux

all: $(NAME)

$(NAME): $(OBJ)
	@if [ ! -f minilibx-linux/libmlx_Linux.a ]; then make -C minilibx-linux; fi
	$(CC) $(CFLAGS) $(OBJ) minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -fr $(NAME)

clean:
	rm -fr $(OBJ_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus


