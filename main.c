/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:12:53 by akostian          #+#    #+#             */
/*   Updated: 2024/07/24 16:32:26 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map->height)
		free(game->map->map[i]);
	free(game->map->map);
	free(game->map);
}

int	return_error(t_game *game, int code)
{
	printf("Error\n");
	if (code == INCORRECT_ARGC_ERROR_CODE)
		printf(INCORRECT_ARGC_MESSAGE);
	if (code == INCORRECT_MAP_PATH_ERROR_CODE)
		printf(INCORRECT_MAP_PATH_ERROR_MESSAGE);
	if (code == MALLOC_ERROR_CODE)
		printf(MALLOC_MESSAGE);
	if (code >= MLX_WINDOW_ERROR_CODE)
		free(game->mlx_ptr);
	if (code >= MAP_IS_INVALID_ERROR_CODE)
	{
		free_game(game);
		printf("ERROR OCCURED");
	}
	exit(0);
	return (-1);
}

int	on_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_game *game)
{
	int	move_code_return;

	if (keysym == Q_KEY || keysym == ESC_KEY)
	{
		on_destroy(game);
		free_game(game);
	}
	if (!is_control_key(keysym))
		return (0);
	move_code_return = game->game_move_player(game->map, keysym);
	if (!move_code_return)
		return (0);
	game->collectibles_count += (move_code_return > 1);
	game->move_count += (move_code_return >= 1);
	if (!(game->map->player_x == game->map->exit_x
			&& game->map->player_y == game->map->exit_y))
		game->map->map[game->map->exit_x][game->map->exit_y] = 'E';
	else if (game->collectibles_count == game->map->collectibles_n)
	{
		on_destroy(game);
		free_game(game);
	}
	game->game_draw_map(game);
	ft_printf("Counter: %d\n", game->move_count);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (return_error(&game, INCORRECT_ARGC_ERROR_CODE));
	if (!mapname_is_valid(argv[1]))
		return (return_error(&game, INCORRECT_MAP_PATH_ERROR_CODE));
	if (read_map(&game, argv[1]) == -1)
		return (return_error(&game, MALLOC_ERROR_CODE));
	if (!map_is_valid(game.map))
		return (return_error(&game, MAP_IS_INVALID_ERROR_CODE));
	game.game_init = game_init;
	game.game_init(&game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask,
		&on_keypress, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &game);
	game.game_draw_map(&game);
	mlx_loop(game.mlx_ptr);
	free_game(&game);
}
