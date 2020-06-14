#include "wolf.h"
/*
**	xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
**	wolf->world.texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y - 1);
**	wolf->world.texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
**	wolf->world.texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
**	wolf->world.texture[4][TEX_WIDTH * y + x] = 256 * xorcolor;
**	wolf->world.texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
**	wolf->world.texture[6][TEX_WIDTH * y + x] = 65536 * (y * 256 / TEX_HEIGHT);
**	wolf->world.texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
*/
void	get_test_textures(t_core *wolf)
{
	int	xorcolor;
	int	x;
	int	y;
	
	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			wolf->world.texture[TEX_MAX_NBR][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			y++;
		}
		x++;
	}
}
