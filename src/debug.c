//HEADER

#include "wolf.h"
#include <stdio.h>
#include <unistd.h>

void	debug_camera(t_camera *cam)
{
	dprintf(STDERR_FILENO, "===> debug_camera()\n");
	dprintf(STDERR_FILENO, "dir x: %f    y: %f\n", cam->dir.x, cam->dir.y);
	dprintf(STDERR_FILENO, "pos x: %f    y: %f\n", cam->pos.x, cam->pos.y);
	dprintf(STDERR_FILENO, "plane x: %f    y: %f\n\n", cam->plane.x, cam->plane.y);
}

void	debug_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	dprintf(STDERR_FILENO, "===> debug_map()\n");
	dprintf(STDERR_FILENO, "width: %d    height: %d\nspawn x: %d    y: %d\n\n", map->width, map->height, map->spawn_x, map->spawn_y);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			dprintf(STDERR_FILENO, "%d ", map->map[j][i]);	
			j++;
		}
		write(STDERR_FILENO, "\n", 1);
		i++;
	}
}
