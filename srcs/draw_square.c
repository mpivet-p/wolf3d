/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:46:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/12 16:52:31 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_square(t_core *wolf, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	x = wolf->world.width - x;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			set_pixel(wolf->img, x * 21 + wolf->world.center[0] + i
				, y * 21 + wolf->world.center[1] + j, color);
			j++;
		}
		i++;
	}
}
