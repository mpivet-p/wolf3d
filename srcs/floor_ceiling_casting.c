/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:54:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/15 04:13:49 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	floor_ceiling_casting(t_core *wolf)
{
	t_vector	floor_step;
	t_vector	floor;
	t_vector	ray1;
	t_vector	ray2;
	double		row_distance;
	int			color;
	int			pos_z;
	int			y;

	ray1.x = dir->x - plane->x;
	ray1.y = dir->y - plane->y;
	ray2.x = dir->x + plane->x;
	ray2.y = dir->y + plane->y;
	pos_z = 0.5 * SIMG_Y;
	while (y < SIMG_Y)
	{
		p = y - SIMG_Y / 2;
		row_distance = pos_z / p;
		floor_step.x = row_distance * (ray2.x - ray1.x) / SIMG_X;
		floor_step.y = row_distance * (ray2.y - ray1.y) / SIMG_X;
		floor.x = pos->x + row_distance + ray1.x;
		floor.y = pos->y + row_distance + ray1.y;
		y++;
	}
}
