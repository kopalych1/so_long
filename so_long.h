/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:15:30 by akostian          #+#    #+#             */
/*   Updated: 2024/07/21 22:34:17 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "libft/include/libft.h"

#define MAP_EXTENSION ".ber"

/* ERRORS */
#define MALLOC_ERROR_CODE 1
#define MALLOC_MESSAGE "MALLOC ERROR\n"

#define INCORRECT_ARGC_ERROR_CODE 2
#define INCORRECT_ARGC_MESSAGE "INCORRECT ARGC\n"

#define INCORRECT_MAP_PATH_ERROR_CODE 3
#define INCORRECT_MAP_PATH_ERROR_MESSAGE "MAP NAME IS TERRIBLE\n"

#define MAP_IS_INVALID_ERROR_CODE 4
#define MAP_IS_INVALID_ERROR_MESSAGE "MAP IS INVALID\n"
/*  */

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		collectibles_n;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	void	(*__init__)(struct s_map *self);
}	t_map;

typedef struct s_game
{
	t_map	*map;
	int		move_count;
	void	(*game__init__)(struct s_game *self);
}	t_game;

void	game__init__(t_game *self);

/* FUNCS */

int		read_map(t_game *game, const char *map_path);

/* ADD TO LIBFT? */

char	**matrix_dup(char **arr, size_t size);
int		append_str_to_arr(char ***arr, size_t *size, char *new_str);

/*  */

int		mapname_is_valid(char *mapname);
int		map_is_valid(t_map *map);

/*  */