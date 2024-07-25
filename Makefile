# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 14:18:31 by akostian          #+#    #+#              #
#    Updated: 2024/07/24 16:21:24 by akostian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= so_long

SRCS		= main.c libft.c parser.c validators.c is_control_key.c game_methods.c mapname_is_valid.c

INCLUDES	= -Iinclude

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror


# MLX FLAGS FOR LINUX
MLX_FLAGS	= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11


RM			= rm -f

MLX_PATH = mlx/
MLX_LIB = $(MLX_PATH)libmlx_Linux.a

all:
	make -C $(MLX_PATH)
	make -C libft/
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(SRCS) $(MLX_FLAGS) $(MLX_LIB) libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	make clean -C libft/
	make clean -C $(MLX_PATH)

fclean: clean
	make fclean -C libft/
	make clean -C $(MLX_PATH)
	$(RM) $(MLX_LIB)

	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re