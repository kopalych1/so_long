/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:12:53 by akostian          #+#    #+#             */
/*   Updated: 2024/07/21 21:53:12 by akostian         ###   ########.fr       */
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
	if (code == MAP_IS_INVALID_ERROR_CODE)
	{
		free_game(game);
		printf(MAP_IS_INVALID_ERROR_MESSAGE);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (argc != 2)
		return (return_error(&game, INCORRECT_ARGC_ERROR_CODE));
	if (!mapname_is_valid(argv[1]))
		return (return_error(&game, INCORRECT_MAP_PATH_ERROR_CODE));
	if (read_map(&game, argv[1]) == -1)
		return (return_error(&game, MALLOC_ERROR_CODE));
	if (!map_is_valid(game.map))
		return (return_error(&game, MAP_IS_INVALID_ERROR_CODE));
	///////
	printf("--------MAP--------\n");
	i = -1;
	while (++i < game.map->height)
		printf("[MAP]:\t\t\t%s\n", game.map->map[i]);
	///////
	free_game(&game);
}
