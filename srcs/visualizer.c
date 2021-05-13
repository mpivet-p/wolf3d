/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:44:26 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/13 23:28:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <mlx.h>

static void	draw_camera(t_core *wolf, t_camera *cam, char *img)
{
	int x;
	int	y;
	int i;
	int	j;

	i = 0;
	x = cam->pos.x * 21.0;
	y = cam->pos.y * 21.0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			set_pixel(img, x + wolf->world.center[0] + i
			, y + wolf->world.center[1] + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void		draw_ray(t_core *wolf, t_vector ray, int color)
{
	t_vector	origin;
	t_vector	dest;

	dest.x = ray.x * 21 + wolf->world.center[0];
	dest.y = ray.y * 21 + wolf->world.center[1];
	origin.x = wolf->cam.pos.x * 21 + wolf->world.center[0];
	origin.y = wolf->cam.pos.y * 21 + wolf->world.center[1];
	bresenham(wolf, origin, dest, color);
}

void		map_visualizer(t_core *wolf)
{
	t_world	*world;
	int		x;
	int		y;

	x = 0;
	if (wolf->cam.mode != WLF_MAP)
		return ;
	world = &(wolf->world);
	ft_bzero(wolf->img, 4 * SIMG_X * SIMG_Y);
	while (x < world->width)
	{
		y = 0;
		while (y < world->height)
		{
			draw_square(wolf, x, y
			, (wolf->world.map[x][y] != 0) ? 0xFFFFFFFF : 0x121212);
			y++;
		}
		x++;
	}
	draw_camera(wolf, &(wolf->cam), wolf->img);
}
