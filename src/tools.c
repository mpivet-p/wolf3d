/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 04:49:56 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/08/22 05:19:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"
#include <mlx.h>

void	set_pixel(char *image, int x, int y, int color)
{
	int i;

	i = (((SIMG_X * y) + x) * 4);
	if (x >= 0 && y >= 0 && x < SIMG_X && y < SIMG_Y)
	{
		image[i + 2] = color & 0xFF0000;
		image[i + 1] = color & 0x00FF00;
		image[i] = color & 0x0000FF;
	}
}

int		quit_wolf(void *param)
{
	t_core *wolf;

	wolf = (t_core*)param;
	if (wolf->mlx && wolf->img)
		mlx_destroy_image(wolf->mlx, wolf->screen);
	if (wolf->mlx && wolf->win)
		mlx_destroy_window(wolf->mlx, wolf->win);
	exit(0);
}
