//HEADER

#include "wolf.h"
#include "libft.h"
#include "mlx.h"

static void	fill_texture(t_world *world, char *img, int tex_i)
{
	int	color;
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	if (!img)
		return ;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			i = ((TEX_WIDTH * y) + x) * 4;
			color = (img[i + 2] << 16) + (img[i + 1] << 8) + img[i];
			world->texture[tex_i][TEX_WIDTH * y + x] = color;
			y++;
		}
		x++;
	}
}

int8_t	file_to_texture(t_core *wolf, t_world *world, char *file, int tex_i)
{
	void	*ptr;
	int		tools[3];
	int		height;
	int		width;

	if (!(ptr = mlx_xpm_file_to_image(wolf->mlx, file, &width, &height)))
	{
		ft_putstr_fd("wolf: texture file error\n", STDERR_FILENO);
		return (FAILURE);
	}
	else if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		ft_putstr_fd("wolf: texture size error\n", STDERR_FILENO);
		return (FAILURE);
	}
	fill_texture(world, mlx_get_data_addr(
		ptr, &(tools[0]), &(tools[1]), &(tools[2])), tex_i);
	mlx_destroy_image(wolf->mlx, ptr);
	return (SUCCESS);
}
