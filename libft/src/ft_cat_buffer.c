/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:41:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/04/27 16:09:40 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cat_buffer(char *buffer, char *tocopy, int i)
{
	int j;

	j = 0;
	if (i < 0)
		i = 0;
	while (i < BF_SIZE && tocopy[j] != 0)
	{
		buffer[i] = tocopy[j];
		buffer[i + 1] = 0;
		j++;
		i++;
	}
	if (i == BF_SIZE)
	{
		write(1, buffer, BF_SIZE);
		ft_strclr(buffer);
		return (ft_cat_buffer(buffer, tocopy + j, 0));
	}
	return (i);
}
