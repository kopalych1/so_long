/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 07:48:44 by akostian          #+#    #+#             */
/*   Updated: 2024/09/19 16:35:45 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	game_draw_map(t_game *self)
{
	int		y;
	int		x;

	y = -1;
	while (++y < self->map->height)
	{
		x = -1;
		while (++x < self->map->width)
		{
			mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
				self->floor_img, x * self->img_width, y * self->img_width);
			if (self->map->map[y][x] == '1')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->wall_img, x * self->img_width, y * self->img_width);
			if (self->map->map[y][x] == 'C')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->coll_img, x * self->img_width, y * self->img_width);
			if (self->map->map[y][x] == 'P')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->player_img, x * self->img_width, y * self->img_width);
			if (self->map->map[y][x] == 'E')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->exit_img, x * self->img_width, y * self->img_width);
		}
	}
}

int	game_move_player(t_map *map, int keysym)
{
	char	*current_char;
	int		is_collectible;
	int		old_player_x;
	int		old_player_y;

	current_char = &(map->map[map->player_y][map->player_x]);
	old_player_x = map->player_x;
	old_player_y = map->player_y;
	if (keysym == D_KEY || keysym == RIGHT_ARROW_KEY)
		if (map->map[map->player_y][map->player_x + 1] != '1')
			map->player_x += 1;
	if (keysym == A_KEY || keysym == LEFT_ARROW_KEY)
		if (map->map[map->player_y][map->player_x - 1] != '1')
			map->player_x -= 1;
	if (keysym == S_KEY || keysym == DOWN_ARROW_KEY)
		if (map->map[map->player_y + 1][map->player_x] != '1')
			map->player_y += 1;
	if (keysym == W_KEY || keysym == UP_ARROW_KEY)
		if (map->map[map->player_y - 1][map->player_x] != '1')
			map->player_y -= 1;
	*current_char = '0';
	is_collectible = (map->map[map->player_y][map->player_x] == 'C');
	map->map[map->player_y][map->player_x] = 'P';
	return (is_collectible + ((old_player_x != map->player_x)
			|| (old_player_y != map->player_y)));
}

void	game_vars_init(t_game *self)
{
	self->game_init = game_init;
	self->game_draw_map = game_draw_map;
	self->game_move_player = game_move_player;
	self->game_verify_images = game_verify_images;
	self->mlx_ptr = NULL;
	self->win_ptr = NULL;
	self->map = NULL;
	self->img_width = IMG_WIDTH;
	self->move_count = 0;
	self->coll_img = NULL;
	self->floor_img = NULL;
	self->player_img = NULL;
	self->wall_img = NULL;
	self->exit_img = NULL;
	self->collectibles_count = 0;
}

void	game_init(t_game *self)
{
	self->mlx_ptr = mlx_init();
	if (!self->mlx_ptr)
		return_error(self, MLX_INIT_ERROR_CODE);
	self->win_ptr = mlx_new_window(self->mlx_ptr,
			self->map->width * IMG_WIDTH,
			self->map->height * IMG_WIDTH, "so long");
	if (!self->win_ptr)
		return_error(self, MLX_WINDOW_ERROR_CODE);
	self->coll_img = mlx_xpm_file_to_image(self->mlx_ptr, "images/key.xpm",
			&self->img_width, &self->img_width);
	self->exit_img = mlx_xpm_file_to_image(self->mlx_ptr, "images/exit.xpm",
			&self->img_width, &self->img_width);
	self->wall_img = mlx_xpm_file_to_image(self->mlx_ptr, "images/wall.xpm",
			&self->img_width, &self->img_width);
	self->floor_img = mlx_xpm_file_to_image(self->mlx_ptr, "images/floor.xpm",
			&self->img_width, &self->img_width);
	self->player_img = mlx_xpm_file_to_image(self->mlx_ptr, "images/player.xpm",
			&self->img_width, &self->img_width);
	self->game_verify_images(self);
}

void	game_verify_images(t_game *self)
{
	if (!self->coll_img
		|| !self->exit_img
		|| !self->floor_img
		|| !self->wall_img
		|| !self->floor_img
		|| !self->player_img)
		return_error(self, MLX_IMAGES_ERROR_CODE);
}
