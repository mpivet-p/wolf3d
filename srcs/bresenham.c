/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:41:30 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:41:32 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	drawline_init(
			t_vector *delta, t_vector *s, t_vector one, t_vector two)
{
	delta->x = two.x - one.x;
	s->x = (delta->x < 0) ? -1 : 1;
	delta->y = two.y - one.y;
	s->y = (delta->y < 0) ? -1 : 1;
}

void		bresenham(t_core *wolf, t_vector one, t_vector two, int color)
{
	t_vector	delta;
	t_vector	s;
	double		slope;
	double		pitch;

	drawline_init(&delta, &s, one, two);
	slope = (fabs(delta.y) < fabs(delta.x)) ? delta.y / delta.x
		: delta.x / delta.y;
	pitch = (fabs(delta.y) < fabs(delta.x)) ? one.y - (slope * one.x)
		: one.x - (slope * one.y);
	if (fabs(delta.y) < fabs(delta.x))
		while ((int)round(one.x) != (int)round(two.x))
		{
			set_pixel(wolf->img, (int)round(one.x),
					(int)lround((slope * one.x) + pitch), color);
			one.x += s.x;
		}
	else
		while ((int)round(one.y) != (int)round(two.y))
		{
			set_pixel(wolf->img, (int)lround((slope * one.y) + pitch),
					(int)round(one.y), color);
			one.y += s.y;
		}
}
