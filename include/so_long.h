/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:15:30 by akostian          #+#    #+#             */
/*   Updated: 2024/07/25 16:59:23 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

# define MAP_EXTENSION ".ber"

/* ERRORS */

# define MALLOC_ERROR_CODE 1
# define MALLOC_MESSAGE "MALLOC ERROR\n"

# define INCORRECT_ARGC_ERROR_CODE 2
# define INCORRECT_ARGC_MESSAGE "INCORRECT ARGC\n"

# define INCORRECT_MAP_PATH_ERROR_CODE 3
# define INCORRECT_MAP_PATH_ERROR_MESSAGE "MAP NAME IS TERRIBLE\n"

# define MAP_IS_INVALID_ERROR_CODE 4
# define MAP_IS_INVALID_ERROR_MESSAGE "MAP IS INVALID\n"

# define MLX_INIT_ERROR_CODE 5
# define MLX_INIT_ERROR_MESSAGE "ERROR WITH MLX INIT\n"

# define MLX_WINDOW_ERROR_CODE 6
# define MLX_WINDOW_ERROR_MESSAGE "ERROR WITH MLX WINDOW\n"

# define MLX_IMAGES_ERROR_CODE 7
# define MLX_IMAGES_ERROR_MESSAGE "ERROR WITH LOADING IMAGES\n"

/* CONTROL KEYS */

# define D_KEY 100
# define A_KEY 97
# define W_KEY 119
# define S_KEY 115

# define RIGHT_ARROW_KEY 65363
# define LEFT_ARROW_KEY 65361
# define UP_ARROW_KEY 65362
# define DOWN_ARROW_KEY 65364

# define ESC_KEY 65307
# define Q_KEY 113

/* IMAGES SETTINGS */

# define IMG_WIDTH 64

# define MAX_WINDOW_WIDTH 1920
# define MAX_WINDOW_HEIGHT 1080

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
	void	*mlx_ptr;
	void	*win_ptr;
	int		img_width;
	void	*wall_img;
	void	*floor_img;
	void	*coll_img;
	void	*player_img;
	void	*exit_img;
	t_map	*map;
	int		move_count;
	int		collectibles_count;
	void	(*game_init)(struct s_game *self);
	void	(*game_draw_map)(struct s_game *self);
	int		(*game_move_player)(t_map *map, int keysym);
	void	(*game_verify_images)(struct s_game *self);
}	t_game;

void	game_init(t_game *self);
void	game_draw_map(t_game *self);
int		game_move_player(t_map *map, int keysym);
void	game_verify_images(t_game *self);
/* FUNCS */

int		return_error(t_game *game, int code);
int		read_map(t_game *game, const char *map_path);
int		is_control_key(int keysym);
int		mapname_is_valid(char *mapname);
int		map_is_valid(t_map *map);

/* ADD TO LIBFT? */

char	**matrix_dup(char **arr, size_t size);
int		append_str_to_arr(char ***arr, size_t *size, char *new_str);

#endif