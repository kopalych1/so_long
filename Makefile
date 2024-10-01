# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 14:18:31 by akostian          #+#    #+#              #
#    Updated: 2024/10/01 15:40:33 by akostian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= so_long

SRC_DIR		= src
SRCS		= main.c \
			  utils.c \
			  parser.c \
			  find_objectives.c \
			  map_validators.c \
			  is_control_key.c \
			  game_methods.c \
			  mapname_is_valid.c

INCLUDES	= -Iinclude

BUILD_DIR	= build
LIBFT_DIR	= libft
OBJS		= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

RM			= rm -rf


UNAME		= $(shell uname -s)

# MLX FLAGS FOR LINUX
ifeq ($(UNAME), Linux)
	MLX_FLAGS		= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
	MLX_C_INC		= -I/usr/include -Imlx_linux -O3
	MLX_PATH		= mlx/
	MLX_LIB			= $(MLX_PATH)libmlx_Linux.a

	KEYS			= -D W_KEY=119 \
					  -D A_KEY=97 \
					  -D S_KEY=115 \
					  -D D_KEY=100 \
					  -D Q_KEY=113 \
					  -D ESC_KEY=65307 \
					  -D UP_ARROW_KEY=65362 \
					  -D LEFT_ARROW_KEY=65361 \
					  -D DOWN_ARROW_KEY=65364 \
					  -D RIGHT_ARROW_KEY=65363

# MLX FLAGS FOR MACOS
else
	MLX_FLAGS		= -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
	MLX_C_INC		= -Imlx_macos
	MLX_PATH		= mlx_macos/
	MLX_LIB			= $(MLX_PATH)libmlx.a

	KEYS			= -D W_KEY=13 \
					  -D A_KEY=0 \
					  -D S_KEY=1 \
					  -D D_KEY=2 \
					  -D Q_KEY=12 \
					  -D ESC_KEY=53 \
					  -D UP_ARROW_KEY=126 \
					  -D LEFT_ARROW_KEY=123 \
					  -D DOWN_ARROW_KEY=125 \
					  -D RIGHT_ARROW_KEY=124

endif


all: $(NAME)
#


$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_PATH)

	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(MLX_LIB) $(LIBFT_DIR)/libft.a
#


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
#


$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)

	$(CC) $(CFLAGS) $(KEYS) $(MLX_C_INC) -c $< -o $@
#


clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

	$(RM) $(BUILD_DIR)
#


fclean:
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_PATH)

	$(RM) $(BUILD_DIR) $(MLX_LIB) $(NAME)
#


re: fclean all
#



.PHONY: all clean fclean re