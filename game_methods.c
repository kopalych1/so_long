/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 07:48:44 by akostian          #+#    #+#             */
/*   Updated: 2024/07/25 16:23:53 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_draw_map(t_game *self)
{
	int		i;
	int		j;

	i = -1;
	while (++i < self->map->height)
	{
		j = -1;
		while (++j < self->map->width)
		{
			mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
				self->floor_img, j * self->img_width, i * self->img_width);
			if (self->map->map[i][j] == '1')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->wall_img, j * self->img_width, i * self->img_width);
			if (self->map->map[i][j] == 'C')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->coll_img, j * self->img_width, i * self->img_width);
			if (self->map->map[i][j] == 'P')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->player_img, j * self->img_width, i * self->img_width);
			if (self->map->map[i][j] == 'E')
				mlx_put_image_to_window(self->mlx_ptr, self->win_ptr,
					self->exit_img, j * self->img_width, i * self->img_width);
		}
	}
}

int	game_move_player(t_map *map, int keysym)
{
	char	*current_char;
	int		is_collectible;
	int		old_player_x;
	int		old_player_y;

	current_char = &(map->map[map->player_x][map->player_y]);
	old_player_x = map->player_x;
	old_player_y = map->player_y;
	if (keysym == D_KEY || keysym == RIGHT_ARROW_KEY)
		if (map->map[map->player_x][map->player_y + 1] != '1')
			map->player_y += 1;
	if (keysym == A_KEY || keysym == LEFT_ARROW_KEY)
		if (map->map[map->player_x][map->player_y - 1] != '1')
			map->player_y -= 1;
	if (keysym == S_KEY || keysym == DOWN_ARROW_KEY)
		if (map->map[map->player_x + 1][map->player_y] != '1')
			map->player_x += 1;
	if (keysym == W_KEY || keysym == UP_ARROW_KEY)
		if (map->map[map->player_x - 1][map->player_y] != '1')
			map->player_x -= 1;
	*current_char = '0';
	is_collectible = (map->map[map->player_x][map->player_y] == 'C');
	map->map[map->player_x][map->player_y] = 'P';
	return (is_collectible + ((old_player_x != map->player_x)
			|| (old_player_y != map->player_y)));
}

void	game_init(t_game *self)
{
	self->game_draw_map = game_draw_map;
	self->game_move_player = game_move_player;
	self->img_width = IMG_WIDTH;
	self->move_count = 0;
	self->collectibles_count = 0;
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
}
