/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:55:47 by akostian          #+#    #+#             */
/*   Updated: 2024/08/16 13:39:48 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	read_map(t_game *game, const char *map_path)
{
	char	*line;
	int		map_fd;
	size_t	i;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (-1);
	map_fd = open(map_path, O_RDONLY);
	line = get_next_line(map_fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (append_str_to_arr(&map->map, &i, line) == -1)
			return (-1);
		line = get_next_line(map_fd);
	}
	map->height = i;
	game->map = map;
	return (0);
}
