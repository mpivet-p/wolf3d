//HEADER

#include "wolf.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>

#include <stdio.h>
#include <unistd.h>

static t_vector	get_delta_dist(t_vector *raydir)
{
	t_vector	delta_dist;

	if (raydir->x == 0)
		delta_dist.x = 1;
	else
		delta_dist.x = (raydir->y == 0) ? 0 : fabs(1.0 / raydir->x);
	if (raydir->y == 0)
		delta_dist.y = 1;
	else
		delta_dist.y = (raydir->x == 0) ? 0 : fabs(1.0 / raydir->y);
	return (delta_dist);
}

static t_vector	get_side_dist(t_camera *cam, t_vector *raydir,
		t_vector *delta_dist, int *step)
{
	t_vector	side_dist;

	if (raydir->x < 0)
	{
		step[0] = -1;
		side_dist.x = (cam->pos.x - round(cam->pos.x)) * delta_dist->x;
	}
	else
	{
		step[0] = 1;
		side_dist.x = (round(cam->pos.x) + 1.0 - cam->pos.x) * delta_dist->x;
	}
	if (raydir->y < 0)
	{
		step[1] = -1;
		side_dist.y = (cam->pos.y - round(cam->pos.y)) * delta_dist->y;
	}
	else
	{
		step[1] = 1;
		side_dist.y = (round(cam->pos.y) + 1.0 - cam->pos.y) * delta_dist->y;
	}
	return (side_dist);
}

static double	intersect(t_core *wolf, t_ray *ray, int *step)
{
	t_vector	delta_dist;

	delta_dist = get_delta_dist(&(ray->dir));
	ray->side_dist = get_side_dist(&(wolf->cam), &(ray->dir), &delta_dist, step);
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
	return ((ray->side == 1) ? ray->side_dist.x : ray->side_dist.y);
}

void	unit(t_vector *dir)
{
	double	norm;

	norm = sqrt(dir->x * dir->x + dir->y * dir->y);
	dir->x /= norm;
	dir->y /= norm;
}

void	draw_map(t_core *wolf, t_ray *ray, double dist, int *step)
{
	draw_square(wolf, ray->map[0], ray->map[1], 0x0000CC);
	if (ray->side == 0)
	{
		draw_ray(wolf, set_vec(ray->map[0] + (step[0] == -1)
			, wolf->cam.pos.y + (ray->dir.y * (dist - 1))), 0x00FF00);
	}
	else
	{
		draw_ray(wolf, set_vec(wolf->cam.pos.x + (ray->dir.x * (dist - 1))
			, ray->map[1] + (step[1] == -1)), 0xFF0000);
	}
}

void	ver_line(t_core *wolf, int x, int color, int start, int end)
{
	while (start < end)
	{
		set_pixel(wolf->img, x, start, color);
		start++;
	}
}

int		get_wall_color(int wall)
{
	static int	wall_colors[] = {0, 0x00FF0000, 0x0000FF00, 0x000000FF};

	return (wall_colors[wall]);
}

void	render_wolf(t_core *wolf, t_ray *ray, int x, int *step)
{
	t_camera	*cam;
	double		pwall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	int			h;

	h = SIMG_Y;
	cam = &(wolf->cam);
	if (ray->side == 0)
		pwall_dist = (ray->map[0] - cam->pos.x + (1 - step[0]) / 2) / ray->dir.x;
	else
		pwall_dist = (ray->map[1] - cam->pos.y + (1 - step[1]) / 2) / ray->dir.y;
	line_height = (int)(h / pwall_dist);
	draw_start = (line_height / -2) + (h / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (line_height / 2) + (h / 2);
	if (draw_end >= h)
		draw_end = h - 1;
	color = get_wall_color(wolf->world.map[ray->map[0]][ray->map[1]]);
	if (ray->side == 1)
		color = color / 2;
	ver_line(wolf, x, color, draw_start, draw_end);
}

void	draw_scene(t_core *wolf)
{
	double		camera_x;
	double		dist;
	t_ray		ray;
	int			step[2];
	int			x;

	x = 0;
	ft_bzero(wolf->img, SIMG_X * SIMG_Y * 4);
	if (wolf->cam.mode == WLF_MAP)
		map_visualizer(wolf);
	while (x < SIMG_X)
	{
		ray.map[0] = (int)round(wolf->cam.pos.x);
		ray.map[1] = (int)round(wolf->cam.pos.y);
		camera_x =  2.0 * x / (double)SIMG_Y - 1;
		ray.dir.x = wolf->cam.dir.x + wolf->cam.plane.x * camera_x;
		ray.dir.y = wolf->cam.dir.y + wolf->cam.plane.y * camera_x;
		dist = intersect(wolf, &ray, step);
		if (wolf->cam.mode == WLF_MAP)
			draw_map(wolf, &ray, dist, step);
		else
			render_wolf(wolf, &ray, x, step);
		x++;
	}
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->screen, 0, 0);
}
