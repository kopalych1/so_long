/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:55:47 by akostian          #+#    #+#             */
/*   Updated: 2024/08/16 18:31:12 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// function desined only to read the rest of the file, to avoid memory leaks
void	read_rest(int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
	}
}

int	read_map(t_game *game, const char *map_path)
{
	char	*line;
	int		map_fd;
	size_t	i;

	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\n"MALLOC_ERROR_MESSAGE), -1);
	game->map->map = NULL;
	map_fd = open(map_path, O_RDONLY);
	line = get_next_line(map_fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (append_str_to_arr(&(game->map->map), &i, line) == -1)
			return (free_arr(game->map->map, i), free(line), read_rest(map_fd),
				free(game->map), ft_printf("Error\n"MALLOC_ERROR_MESSAGE), -1);
		line = get_next_line(map_fd);
	}
	game->map->height = i;
	close(map_fd);
	return (0);
}
