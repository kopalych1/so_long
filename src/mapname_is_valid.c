/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapname_is_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:43:13 by akostian          #+#    #+#             */
/*   Updated: 2024/07/24 13:43:54 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mapname_is_valid(char *mapname)
{
	size_t	mapname_len;
	size_t	i;

	mapname_len = ft_strlen(mapname);
	i = ft_strlen(MAP_EXTENSION);
	if (mapname_len < i)
		return (0);
	while (i)
		if (mapname[mapname_len--] != MAP_EXTENSION[i--])
			return (0);
	return (1);
}
