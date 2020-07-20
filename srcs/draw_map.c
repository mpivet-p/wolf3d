/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:42:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:42:27 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_map(t_core *wolf, t_ray *ray, int *step)
{
	draw_square(wolf, ray->map[0], ray->map[1], 0x0000CC);
	if (ray->side == 0)
	{
		draw_ray(wolf, set_vec(ray->map[0] + (step[0] == -1)
			, wolf->cam.pos.y
				+ (ray->dir.y * (ray->side_dist.x - 1))), 0x00FF00);
	}
	else
	{
		draw_ray(wolf, set_vec(
			wolf->cam.pos.x + (ray->dir.x * (
			ray->side_dist.y - 1)), ray->map[1] + (step[1] == -1)), 0x00FF00);
	}
}
