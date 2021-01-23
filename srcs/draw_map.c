/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:42:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/01/23 17:06:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <unistd.h>

void	draw_map(t_core *wolf, t_ray *ray, int *step)
{
	t_vector delta_dist;

	delta_dist = get_delta_dist(&(ray->dir));
	if (wolf->cam.mode != WLF_MAP)
		return ;
	draw_square(wolf, ray->map[0], ray->map[1], 0x0000CC);
	if (ray->side == 0)
	{
		if (step[0] < 0)
			draw_ray(wolf, set_vec(ray->map[0] + 1, ray->map[1] + ), 0xFF0000);
		else
			draw_ray(wolf, set_vec(ray->map[0], ray->map[1] - delta_dist.x), 0xFF0000);
	}
	else
	{
		if (step[1] < 0)
			draw_ray(wolf, set_vec(ray->map[0], ray->map[1] + 1), 0x00FF00);
		else
			draw_ray(wolf, set_vec(ray->map[0], ray->map[1]), 0x00FF00);
	}
}
