//DEFINE

#include "wolf.h"
#include "libft.h"

void	init_camera(t_camera *cam, t_world *world)
{
	cam->pos.x = world->spawn_x;
	cam->pos.y = world->spawn_y;
	cam->dir.x = 1;
	cam->dir.y = 0;
	cam->plane.x = 0;
	cam->plane.y = 0.66;
}
