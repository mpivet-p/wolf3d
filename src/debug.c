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

void	debug_map(t_world *world)
{
	int	i;
	int	j;

	i = 0;
	dprintf(STDERR_FILENO, "===> debug_map()\n");
	dprintf(STDERR_FILENO, "width: %d    height: %d\nspawn x: %d    y: %d\n\n", world->width, world->height, world->spawn_x, world->spawn_y);
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			dprintf(STDERR_FILENO, "%d ", world->map[j][i]);	
			j++;
		}
		write(STDERR_FILENO, "\n", 1);
		i++;
	}
}
