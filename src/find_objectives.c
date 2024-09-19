/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_objectives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:30:13 by akostian          #+#    #+#             */
/*   Updated: 2024/09/18 00:30:13 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	find_player(t_map *map)
{
	int	x;
	int	y;

	map->player_x = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == 'P')
			{
				if (map->player_x)
					return (0);
				map->player_x = x;
				map->player_y = y;
			}
		}
	}
	return (map->player_x);
}

int	find_objectives(t_map *map)
{
	int	x;
	int	y;

	map->exit_x = 0;
	map->collectibles_n = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == 'C')
				map->collectibles_n += 1;
			if (map->map[y][x] == 'E')
			{
				if (map->exit_x)
					return (0);
				map->exit_x = x;
				map->exit_y = y;
			}
		}
	}
	return (map->exit_x && (map->collectibles_n > 0));
}
