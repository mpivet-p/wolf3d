#include "wolf.h"
#include "libft.h"
#include <mlx.h>
#include <stdio.h>

static void	center_map(int width, int height, int sq_size, int *shift)
{
	shift[0] = (SIMG_X - (width * sq_size)) / 2.0;
	shift[1] = (SIMG_Y - (height * sq_size)) / 2.0;
}

static void	draw_square(t_core *wolf, int *center, int x, int y)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	color = (wolf->world.map[x][y] != 0) ? 0xFFFFFFFF : 0x121212;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			set_pixel(wolf->img, x * 21 + center[0] + i
				, y * 21 + center[1] + j, color);
			j++;
		}
		i++;
	}
}

void	draw_camera(t_camera *cam, char *img, int *center)
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
			set_pixel(img, x + center[0] + i, y + center[1] + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void		draw_ray(t_core *wolf, t_vector ray)
{
	t_vector	origin;
	t_vector	dest;
	int			shift[2];

	center_map(wolf->world.width, wolf->world.height, 21, shift);
	dest.x = ray.x * 21 + shift[0];
	dest.y = ray.y * 21 + shift[1];
	origin.x = wolf->cam.pos.x * 21 + shift[0];
	origin.y = wolf->cam.pos.y * 21 + shift[1];
	bresenham(wolf, origin, dest, 0x0000FF00);

}

void		map_visualizer(t_core *wolf)
{
	t_world	*world;
	int		center[2];
	int		x;
	int		y;

	x = 0;
	world = &(wolf->world);
	ft_bzero(wolf->img, 4 * SIMG_X * SIMG_Y);
	center_map(world->width, world->height, 21, center);
	while (x < world->width)
	{
		y = 0;
		while (y < world->height)
		{
			draw_square(wolf, center, x, y);
			y++;
		}
		x++;
	}
	draw_camera(&(wolf->cam), wolf->img, center);
}
