#include "wolf.h"

t_vector	get_side_dist(t_camera *cam, t_ray *ray,
				t_vector *delta_dist, int *step)
{
	t_vector	side_dist;

	if (ray->dir.x < 0)
	{
		step[0] = -1;
		side_dist.x = (cam->pos.x - ray->map[0]) * delta_dist->x;
	}
	else
	{
		step[0] = 1;
		side_dist.x = (ray->map[0] + 1.0 - cam->pos.x) * delta_dist->x;
	}
	if (ray->dir.y < 0)
	{
		step[1] = -1;
		side_dist.y = (cam->pos.y - ray->map[1]) * delta_dist->y;
	}
	else
	{
		step[1] = 1;
		side_dist.y = (ray->map[1] + 1.0 - cam->pos.y) * delta_dist->y;
	}
	return (side_dist);
}
