/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:22:58 by akostian          #+#    #+#             */
/*   Updated: 2024/08/16 13:39:25 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == '*')
		return ;
	map[x][y] = '*';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	map_is_completable(t_map *map)
{
	char	**flooded_map;
	int		i;
	int		j;

	flooded_map = matrix_dup(map->map, map->height);
	flood_fill(flooded_map, map->player_x, map->player_y);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (flooded_map[i][++j])
			if (flooded_map[i][j] == 'E' || flooded_map[i][j] == 'C')
				return (0);
	}
	i = -1;
	while (++i < map->height)
		free(flooded_map[i]);
	free(flooded_map);
	return (1);
}

// Has to be a separate function, because of the norms
int	find_player(t_map *map)
{
	int	i;
	int	j;

	map->player_x = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'P')
			{
				if (map->player_x)
					return (0);
				map->player_x = i;
				map->player_y = j;
			}
		}
	}
	return (map->player_x);
}

int	find_objectives(t_map *map)
{
	int	i;
	int	j;

	map->exit_x = 0;
	map->collectibles_n = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'C')
				map->collectibles_n += 1;
			if (map->map[i][j] == 'E')
			{
				if (map->exit_x)
					return (0);
				map->exit_x = i;
				map->exit_y = j;
			}
		}
	}
	return (map->exit_x && (map->collectibles_n > 0));
}

int	map_is_valid(t_map *map)
{
	int	i;
	int	j;

	if (map->width > MAX_WINDOW_WIDTH / IMG_WIDTH
		|| map->height > MAX_WINDOW_HEIGHT / IMG_WIDTH)
		return (0);
	map->width = -1;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->map[i][++j])
			if ((i == 0 || j == 0) && (map->map[i][j] != '1'))
				return (0);
		if (map->width >= 0 && map->width != j)
			return (0);
		map->width = j;
	}
	if (find_player(map) && find_objectives(map))
		return (map_is_completable(map));
	return (0);
}
