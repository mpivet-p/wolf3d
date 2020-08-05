/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 04:49:56 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/05 16:08:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"
#include <mlx.h>

void		set_pixel(char *image, int x, int y, int color)
{
	int i;

	i = (((SIMG_X * y) + x) * 4);
	if (x >= 0 && y >= 0 && x < SIMG_X && y < SIMG_Y)
	{
		image[i + 2] = (color & 0x00FF0000) >> 16;
		image[i + 1] = (color & 0x0000FF00) >> 8;
		image[i] = color & 0x000000FF;
	}
}

t_vector	set_vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

int			quit_wolf(void *param)
{
	t_core *wolf;

	wolf = (t_core*)param;
	if (wolf->mlx && wolf->img)
		mlx_destroy_image(wolf->mlx, wolf->screen);
	if (wolf->mlx && wolf->win)
		mlx_destroy_window(wolf->mlx, wolf->win);
	if (wolf->socket > -1)
		sendto(wolf->socket, "", 1, 0
			, (struct sockaddr*)&(wolf->sin), sizeof(struct sockaddr));
	exit(0);
}

void		center_map(int width, int height, int sq_size, int *shift)
{
	shift[0] = (SIMG_X - (width * sq_size)) / 2;
	shift[1] = (SIMG_Y - (height * sq_size)) / 2;
}
