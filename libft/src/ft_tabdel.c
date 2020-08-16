/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 14:21:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/16 14:21:49 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***array)
{
	size_t	i;
	char	**ptr;

	i = 0;
	if (array && *array)
	{
		ptr = *array;
		array = NULL;
		while (ptr[i])
		{
			ft_strdel(&(ptr[i]));
			i++;
		}
		free(ptr);
	}
}
