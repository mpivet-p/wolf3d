/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:06:32 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:06:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

int8_t	get_index(char **array, char *key)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], key) == 0)
			return (i);
		i++;
	}
	if (i < TEX_MAX && (array[i] = ft_strdup(key)) != NULL)
		return (i);
	return (-1);
}
