/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:09:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/21 16:14:28 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	intersect(t_core *wolf, t_ray *ray, int *step)
{
	t_vector	delta_dist;

	delta_dist = get_delta_dist(&(ray->dir));
	ray->side_dist = get_side_dist(&(wolf->cam), ray, &delta_dist, step);
	while (ray->map[0] < wolf->world.width && ray->map[1] < wolf->world.height)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += delta_dist.x;
			ray->map[0] += step[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += delta_dist.y;
			ray->map[1] += step[1];
			ray->side = 1;
		}
		if (wolf->world.map[ray->map[0]][ray->map[1]] != 0)
			break ;
	}
}
