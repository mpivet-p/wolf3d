/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:41:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/13 00:01:43 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_camera(t_camera *cam, t_world *world)
{
	cam->pos.x = world->spawn_x;
	cam->pos.y = world->spawn_y;
	cam->dir.x = -1;
	cam->dir.y = 0;
	cam->plane.x = 0;
	cam->plane.y = 0.66;
	cam->mode = WLF_RENDER;
}

int		check_box(t_camera *cam, t_vector d, t_world *world)
{
	if (world->map[(int)(cam->pos.x + 2 * d.x)][(int)(cam->pos.y)] != 0)
		return (0);
	if (world->map[(int)(cam->pos.x)][(int)(cam->pos.y + 2 * d.y)] != 0)
		return (0);
	return (1);
}
