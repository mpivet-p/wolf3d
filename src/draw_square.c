#include "wolf.h"

void	draw_square(t_core *wolf, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			set_pixel(wolf->img, x * 21 + wolf->world.center[0] + i
				, y * 21 + wolf->world.center[1] + j, color);
			j++;
		}
		i++;
	}
}
