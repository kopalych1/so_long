/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:22:58 by akostian          #+#    #+#             */
/*   Updated: 2024/09/18 00:33:08 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	flood_fill(t_map *map, char **flooded_map, int y, int x)
{
	if (y >= map->height)
		return ;
	if (x >= map->width)
		return ;
	if (flooded_map[y][x] == '1' || flooded_map[y][x] == '*')
		return ;
	flooded_map[y][x] = '*';
	flood_fill(map, flooded_map, y, x + 1);
	flood_fill(map, flooded_map, y, x - 1);
	flood_fill(map, flooded_map, y + 1, x);
	flood_fill(map, flooded_map, y - 1, x);
}

int	map_is_completable(t_map *map)
{
	char	**flooded_map;
	int		y;
	int		x;

	flooded_map = matrix_dup(map->map, map->height);
	if (!flooded_map)
		return (ft_printf("Error\n"MALLOC_ERROR_MESSAGE), 0);
	flood_fill(map, flooded_map, map->player_y, map->player_x);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (flooded_map[y][++x])
		{
			if (flooded_map[y][x] == 'E' || flooded_map[y][x] == 'C')
			{
				ft_printf("Error\n"MAP_IS_NOT_COMPLETABLE_ERROR_MESSAGE);
				return (free_arr(flooded_map, map->height), 0);
			}
		}
	}
	return (free_arr(flooded_map, map->height), 1);
}

int	walls_are_correct(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if ((x > 0 && x < (map->width - 1))
				&& (y > 0 && y < (map->height - 1)))
				continue ;
			if (map->map[y][x] != '1')
				return (0);
		}
	}
	return (1);
}

int	map_is_valid(t_map *map)
{
	int	y;
	int	x;

	map->width = -1;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map[y][++x])
			;
		if (map->width >= 0 && map->width != x)
			return (ft_printf("Error\n"MAP_IS_NOT_RECTANGULAR_ERROR_MESSAGE),
				0);
		map->width = x;
	}
	if (map->width > MAX_WINDOW_WIDTH / IMG_WIDTH
		|| map->height > MAX_WINDOW_HEIGHT / IMG_WIDTH)
		return (ft_printf("Error\n"MAP_IS_TOO_BIG_ERROR_MESSAGE), 0);
	if (!walls_are_correct(map))
		return (ft_printf("Error\n"WALLS_INVALID_ERROR_MESSAGE), 0);
	if (find_player(map) && find_objectives(map))
		return (map_is_completable(map));
	return (ft_printf("Error\n"MAP_IS_INVALID_ERROR_MESSAGE), 0);
}
