/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:54:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/23 14:15:40 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	draw_lines(t_core *wolf, t_vector *floor, int y)
{
	t_vecint	cell;
	t_vecint	tex;
	int			color;
	int			tex_num;
	int			x;

	x = 0;
	while (++x < SIMG_X)
	{
		cell.x = (int)(floor[1].x);
		cell.y = (int)(floor[1].y);
		tex.x = (int)(TEX_WIDTH * (floor[1].x - cell.x)) & (TEX_WIDTH - 1);
		tex.y = (int)(TEX_HEIGHT * (floor[1].y - cell.y)) & (TEX_HEIGHT - 1);
		floor[1].x += floor[0].x;
		floor[1].y += floor[0].y;
		if ((tex_num = wolf->world.ceiling) >= 0)
		{
			color = wolf->world.texture[tex_num][TEX_WIDTH * tex.y + tex.x];
			set_pixel(wolf->img, x, y, ((color >> 1) & 0x7F7F7F));
		}
		if ((tex_num = wolf->world.floor) >= 0)
		{
			color = wolf->world.texture[tex_num][TEX_WIDTH * tex.y + tex.x];
			set_pixel(wolf->img, x, SIMG_Y - y - 1, ((color >> 1) & 0x7F7F7F));
		}
	}
}
void	floor_ceiling_casting(t_core *wolf)
{
	t_vector	floor[2];
	t_vector	dir[2];
	double		row_distance;
	double		pos_z;
	int			p;
	int			y;

	dir[0].x = wolf->cam.dir.x - wolf->cam.plane.x;
	dir[0].y = wolf->cam.dir.y - wolf->cam.plane.y;
	dir[1].x = wolf->cam.dir.x + wolf->cam.plane.x;
	dir[1].y = wolf->cam.dir.y + wolf->cam.plane.y;
	pos_z = SIMG_Y / 2;
	y = 0;
	while (y < pos_z)
	{
		p = y - SIMG_Y / 2;
		row_distance = pos_z / p;
		floor[0].x = row_distance * (dir[1].x - dir[0].x) / SIMG_X;
		floor[0].y = row_distance * (dir[1].y - dir[0].y) / SIMG_X;
		floor[1].x = row_distance * dir[0].x - wolf->cam.pos.x;
		floor[1].y = row_distance * dir[0].y - wolf->cam.pos.y;
		draw_lines(wolf, floor, y);
		y++;
	}
}
