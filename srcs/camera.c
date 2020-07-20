/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:41:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:41:47 by mpivet-p         ###   ########.fr       */
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
