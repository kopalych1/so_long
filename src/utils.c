/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:38:13 by akostian          #+#    #+#             */
/*   Updated: 2024/09/19 14:48:32 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_arr(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

char	**matrix_dup(char **arr, size_t size)
{
	size_t	i;
	char	**arr_cpy;

	arr_cpy = (char **)malloc(size * sizeof(char *));
	if (!arr_cpy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr_cpy[i] = ft_strdup(arr[i]);
		if (!arr_cpy[i])
			return (free_arr(arr_cpy, i), NULL);
		i++;
	}
	return (arr_cpy);
}

int	append_str_to_arr(char ***arr, size_t *size, char *new_str)
{
	char	**old_arr;
	char	**tmp;
	size_t	i;

	old_arr = *arr;
	tmp = (char **)malloc((*size + 1) * sizeof(char *));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < *size)
	{
		tmp[i] = old_arr[i];
		i++;
	}
	tmp[*size] = new_str;
	*arr = tmp;
	(*size)++;
	free(old_arr);
	return (0);
}
