//DEFINE

#include "wolf.h"
#include "libft.h"

void	init_camera(t_camera *cam, t_map *map)
{
	cam->pos.x = map->spawn_x;
	cam->pos.y = map->spawn_y;
	cam->dir.x = -1;
	cam->dir.y = 0;
	cam->plane.x = 0;
	cam->plane.y = 0.66;
}
