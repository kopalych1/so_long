/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:55:47 by akostian          #+#    #+#             */
/*   Updated: 2024/09/19 16:26:07 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	read_map(t_game *game, const char *map_path)
{
	char	*line;
	int		map_fd;
	size_t	i;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (ft_printf("Error\n"MAP_OPEN_ERROR_MESSAGE), -1);
	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\n"MALLOC_ERROR_MESSAGE), -1);
	game->map->map = NULL;
	line = get_next_line(map_fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (append_str_to_arr(&(game->map->map), &i, line) == -1)
			return (free_arr(game->map->map, i), free(line),
				ft_printf("Error\n"MALLOC_ERROR_MESSAGE), -1);
		line = get_next_line(map_fd);
	}
	game->map->height = i;
	close(map_fd);
	return (0);
}
