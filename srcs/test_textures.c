#include "wolf.h"

void	get_test_textures(t_core *wolf)
{
	int	xorcolor;
	int	xycolor;
	int	x;
	int	y;
	
	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;

			wolf->world.texture[0][TEX_WIDTH * y + x] = 0x10000 * 254 * (x != y && x != TEX_WIDTH - y); // flat red with black-cross
			wolf->world.texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 0x10000 * xycolor; // sloped grayscale
			wolf->world.texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 0x10000 * xycolor; // sloped yellow gradient
			wolf->world.texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 0x10000 * xorcolor; //xor grayscale
			wolf->world.texture[4][TEX_WIDTH * y + x] = 256 * xorcolor; // xorcolor
			wolf->world.texture[5][TEX_WIDTH * y + x] = 0x10000 * 192 * (x % 16 && y % 16); // red bricks
			wolf->world.texture[6][TEX_WIDTH * y + x] = 0x10000 * (y * 256 / TEX_HEIGHT); //red gradient
			wolf->world.texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 0x10000 * 128; // flat grey texture
			y++;
		}
		x++;
	}
}
