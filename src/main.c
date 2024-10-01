/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:12:53 by akostian          #+#    #+#             */
/*   Updated: 2024/10/01 16:07:54 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_game(t_game *game)
{
	free_arr(game->map->map, game->map->height);
	free(game->map);
	free(game->mlx_ptr);
	free(game->wall_img);
	free(game->floor_img);
	free(game->coll_img);
	free(game->player_img);
	free(game->exit_img);
}

void	return_error(t_game *game, int code)
{
	ft_printf("Error\n");
	free_game(game);
	if (code == MLX_INIT_ERROR_CODE)
		ft_printf(MLX_INIT_ERROR_MESSAGE);
	if (code == MLX_WINDOW_ERROR_CODE)
		ft_printf(MLX_WINDOW_ERROR_MESSAGE);
	if (code == MLX_IMAGES_ERROR_CODE)
		ft_printf(MLX_IMAGES_ERROR_MESSAGE);
	exit(0);
}

int	on_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_game(game);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_game *game)
{
	int	move_code_return;

	if (keysym == Q_KEY || keysym == ESC_KEY)
		on_destroy(game);
	if (!is_control_key(keysym))
		return (0);
	move_code_return = game->game_move_player(game->map, keysym);
	if (!move_code_return)
		return (0);
	game->collectibles_count += (move_code_return > 1);
	game->move_count += (move_code_return >= 1);
	ft_printf("Counter: %d\n", game->move_count);
	if (!(game->map->player_x == game->map->exit_x
			&& game->map->player_y == game->map->exit_y))
		game->map->map[game->map->exit_y][game->map->exit_x] = 'E';
	else if (game->collectibles_count == game->map->collectibles_n)
		on_destroy(game);
	game->game_draw_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Error\n"INCORRECT_ARGC_MESSAGE), -1);
	if (!mapname_is_valid(argv[1]))
		return (ft_printf("Error\n"INCORRECT_MAP_EXTENSION_ERROR_MESSAGE), -1);
	game_vars_init(&game);
	if (read_map(&game, argv[1]) == -1)
		return (free(game.map), -1);
	if (!map_is_valid(game.map))
		return (free_game(&game), -1);
	game.game_init(&game);
	mlx_key_hook(game.win_ptr, on_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, on_destroy, &game);
	game.game_draw_map(&game);
	mlx_loop(game.mlx_ptr);
	free_game(&game);
}
