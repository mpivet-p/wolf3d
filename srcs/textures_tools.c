/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:07:26 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/21 15:32:34 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"

/*
**	xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
**	wolf->world.texture[0][TEX_WIDTH * y + x] = 65536 * 254
**	* (x != y && x != TEX_WIDTH - y - 1);
**	wolf->world.texture[1][TEX_WIDTH * y + x] = xycolor + 256
**	* xycolor + 65536 * xycolor;
**	wolf->world.texture[2][TEX_WIDTH * y + x] = 256
**	* xycolor + 65536 * xycolor;
**	wolf->world.texture[4][TEX_WIDTH * y + x] = 256 * xorcolor;
**	wolf->world.texture[5][TEX_WIDTH * y + x] = 65536
**	* 192 * (x % 16 && y % 16);
**	wolf->world.texture[6][TEX_WIDTH * y + x] = 65536 * (y * 256 / TEX_HEIGHT);
**	wolf->world.texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
**	xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
**	wolf->world.texture[TEX_MAX_NBR][TEX_WIDTH * y + x] = xorcolor + 256
**	* xorcolor + 65536 * xorcolor;
*/

void		get_test_textures(t_core *wolf)
{
	int	x;
	int	y;

	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			if ((x + (y / 16 * 16)) % (TEX_HEIGHT / 2) < TEX_HEIGHT / 4)
				wolf->world.texture[TEX_MAX][TEX_WIDTH * y + x] = 0xFF00FF;
			else
				wolf->world.texture[TEX_MAX][TEX_WIDTH * y + x] = 0;
			y++;
		}
		x++;
	}
}

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

int8_t		file_to_texture(t_core *wolf, t_world *world, char *file, int tex_i)
{
	void	*ptr;
	int		tools[3];
	int		height;
	int		width;

	if (!(ptr = mlx_xpm_file_to_image(wolf->mlx, file, &width, &height)))
	{
		ft_putstr_fd("wolf: texture file error\n", STDERR_FILENO);
		return (1);
	}
	else if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		ft_putstr_fd("wolf: texture size error\n", STDERR_FILENO);
		return (1);
	}
	fill_texture(world, mlx_get_data_addr(
		ptr, &(tools[0]), &(tools[1]), &(tools[2])), tex_i);
	mlx_destroy_image(wolf->mlx, ptr);
	return (0);
}

int			register_new_texture(
		t_core *wolf, char **prp, char **files, int *tex_i)
{
	int	tex_num;

	if ((tex_num = get_index(files, prp[1])) < 0)
		return (FAILURE);
	if (tex_num == *tex_i)
	{
		if (file_to_texture(wolf, &(wolf->world), prp[1], *tex_i) != 0)
			return (FAILURE);
		(*tex_i)++;
	}
	return (tex_num);
}

int			get_tex_dir(t_wall *wall, t_ray *ray)
{
	int		ret;

	if (wall->tex_id[1] == 0)
		ret = TEX_ALL;
	else if (ray->side == 0 && ray->dir.x > 0)
	{
		ret = TEX_EAST;
	}
	else if (ray->side == 0 && ray->dir.x < 0)
	{
		ret = TEX_WEST;
	}
	else if (ray->side == 1 && ray->dir.y > 0)
	{
		ret = TEX_NORTH;
	}
	else
	{
		ret = TEX_SOUTH;
	}
	ret = wall->tex_id[ret] - 1;
	return ((ret < 0) ? TEX_MAX : ret);
}
