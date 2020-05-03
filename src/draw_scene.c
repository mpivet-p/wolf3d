//HEADER

#include "wolf.h"
#include <math.h>

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

static double	intersect(t_core *wolf, t_vector *raydir, int *map, int *side)
{
	t_vector	delta_dist;
	t_vector	side_dist;
	int			step[2];
	int			hit;

	hit = 0;
	delta_dist = get_delta_dist(raydir);
	side_dist = get_side_dist(&(wolf->cam), raydir, &delta_dist, step);
	while (hit == 0 && map[0] < wolf->world.width && map[1] < wolf->world.height)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map[0] += step[0];
			*side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map[1] += step[1];
			*side = 1;
		}
		if (wolf->world.map[map[0]][map[1]] != 0)
			hit = 1;
	}
	if (hit != 0)
		draw_ray(wolf, set_vec(map[0], map[1]));
	return (side_dist.y);
}

void	unit(t_vector *dir)
{
	double	norm;

	norm = sqrt(dir->x * dir->x + dir->y * dir->y);
	dir->x /= norm;
	dir->y /= norm;
}

void	draw_scene(t_core *wolf)
{
	t_vector	raydir;
	double		camera_x;
	int			map[2];
	int			side;
	int			x;

	x = 0;
	while (x < 10)
	{
		side = 0;
		map[0] = (int)round(wolf->cam.pos.x);
		map[1] = (int)round(wolf->cam.pos.y);
		camera_x =  2.0 * x / (double)10.0 - 1;
		raydir.x = wolf->cam.dir.x + wolf->cam.plane.x * camera_x;
		raydir.y = wolf->cam.dir.y + wolf->cam.plane.y * camera_x;
		unit(&raydir);
		intersect(wolf, &raydir, map, &side);
		x++;
	}
}
