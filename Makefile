# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 14:18:31 by akostian          #+#    #+#              #
#    Updated: 2024/09/19 14:29:58 by akostian         ###   ########.fr        #
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

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3

RM			= rm -rf

# MLX FLAGS FOR LINUX
MLX_FLAGS	= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

# MLX COMPILE FLAGS FOR LINUX
MLX_C_FLAGS	= -I/usr/include -Imlx_linux -O3

MLX_PATH	= mlx/
MLX_LIB		= $(MLX_PATH)libmlx_Linux.a



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

	$(CC) $(CFLAGS) $(MLX_C_FLAGS) -c $< -o $@
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