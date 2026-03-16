NAME = cube3d
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Werror -Wextra -Iminilibx-linux

all: $(NAME) 

$(NAME): $(OBJ)
	make -C minilibx-linux 
	$(CC) $(CFLAGS) $(OBJ) minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -fr $(OBJ_DIR)

clean: 
	rm -fr $(OBJ)

re: fclean all

.PHONY: all clean fclean re


