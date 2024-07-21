/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostian <akostian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:38:13 by akostian          #+#    #+#             */
/*   Updated: 2024/07/21 22:34:22 by akostian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (tmp)
	{
		i = 0;
		while (i < *size)
		{
			tmp[i] = (*arr)[i];
			i++;
		}
		tmp[*size] = new_str;
		*arr = tmp;
		(*size)++;
		free(old_arr);
		return (0);
	}
	else
		return (-1);
}
