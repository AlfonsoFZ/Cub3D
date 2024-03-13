

NAME = cub3D

ifeq ($(shell uname), Darwin)
	INCFLAGS =  -DEBUG=1 -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
else
	INCFLAGS = -ldl -DEBUG=1 -Iinclude -lglfw -L"usr/lib/x86_64-linux-gnu/"
endif

SRC =	src/main.c								\
		src/get_next_line/get_next_line.c	  	\
		src/get_next_line/get_next_line_utils.c	\
		src/utils/ft_strcmp.c					\
		src/utils/utils.c						\
		src/parse/checkmapfile.c				\
		src/parse/readandfill.c					\
		src/parse/checktextures.c				\
		src/free/free.c							\
		src/utils/ft_print_matrix.c				\
		src/parse/fill_mx.c						\
		src/parse/fill_mx_utils.c				\
		src/parse/checkmapcontent.c				\
		src/parse/colorsandplayer.c				\
		src/drawings/initscreen.c				\
		src/drawings/start_drawing.c			\
		src/drawings/drawing_numbers.c			\
		src/keys/keys.c

OBJ_DIR = objt

OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC)))

LIBFT_DIR = ./libft

LIBFT = libft/libft.a

MLX42_DIR = ./MLX42

MLX42 = $(MLX42_DIR)/libmlx42.a

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAKEFLAGS += --quiet

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lm $(LIBFT) $(MLX42) $(INCFLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
		$(MAKE) -C $(MLX42_DIR)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		$(MAKE) clean -C $(MLX42_DIR)
		$(RM) -r $(OBJ_DIR)

fclean: clean
		$(RM) $(LIBFT)
		$(RM) $(MLX42)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
