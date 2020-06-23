//HEADER

#include "wolf.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>

static void	intersect(t_core *wolf, t_ray *ray, int *step)
{
	t_vector	delta_dist;

	delta_dist = get_delta_dist(&(ray->dir));
	ray->side_dist = get_side_dist(&(wolf->cam), ray, &delta_dist, step);
	while (ray->map[0] < wolf->world.width && ray->map[1] < wolf->world.height)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += delta_dist.x;
			ray->map[0] += step[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += delta_dist.y;
			ray->map[1] += step[1];
			ray->side = 1;
		}
		if (wolf->world.map[ray->map[0]][ray->map[1]] != 0)
			break ;
	}
}

void	draw_vert(t_core *wolf, int x, int *start_end, t_ray *ray)
{
	double	line_height;
	double	tex_pos;
	double	step;
	int		tex_y;
	int		color;
	int		i;

//	i = -1;
	line_height = (int)(SIMG_Y / ray->wall_dist);
	step = 1.0 * TEX_HEIGHT / line_height;
	tex_pos = (start_end[0] - SIMG_Y / 2 + line_height / 2) * step;
	i = start_end[0];
//	while (++i < start_end[0])
//		set_pixel(wolf->img, x, i, 0x7FC7E3);
	while (i < start_end[1])
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = wolf->world.texture[ray->tex_num][TEX_HEIGHT * tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		set_pixel(wolf->img, x, i, color);
		i++;
	}
}

int		get_texture_x(t_camera *cam, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = cam->pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = cam->pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	return (tex_x);
}

int		get_tex_dir(t_wall *wall, t_ray *ray)
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
	return ((ret < 0) ? TEX_MAX_NBR : ret);
}

void	render_wolf(t_core *wolf, t_ray *ray, int x, int *step)
{
	int			line_height;
	int			start_end[2];
	double		tmp;

	if (ray->side == 0)
		ray->wall_dist = (ray->map[0] - wolf->cam.pos.x + (1 - step[0]) / 2) / ray->dir.x;
	else
		ray->wall_dist = (ray->map[1] - wolf->cam.pos.y + (1 - step[1]) / 2) / ray->dir.y;
	line_height = (int)(SIMG_Y / ray->wall_dist);
	tmp = (line_height / -2) + (SIMG_Y / 2);
	start_end[0] = (tmp < 0) ? 0 : tmp;
	tmp = (line_height / 2) + (SIMG_Y / 2);
	start_end[1] = (tmp >= SIMG_Y) ? SIMG_Y - 1 : tmp;
	ray->tex_x = get_texture_x(&(wolf->cam), ray);
	ray->tex_num = wolf->world.map[ray->map[0]][ray->map[1]];
	ray->tex_num = get_tex_dir(&(wolf->world.wall[ray->tex_num]), ray);
	draw_vert(wolf, x, start_end, ray);
}

void	draw_scene(t_core *wolf)
{
	double		camera_x;
	double		z_buffer[SIMG_X];
	t_ray		ray;
	int			step[2];
	int			x;

	x = 0;
	ft_bzero(wolf->img, SIMG_X * SIMG_Y * 4);
	if (wolf->cam.mode == WLF_MAP)
		map_visualizer(wolf);
	else
		floor_ceiling_casting(wolf);
	while (x < SIMG_X)
	{
		ray.map[0] = (int)(wolf->cam.pos.x);
		ray.map[1] = (int)(wolf->cam.pos.y);
		camera_x =  2.0 * x / (double)SIMG_X - 1;
		ray.dir.x = wolf->cam.dir.x + wolf->cam.plane.x * camera_x;
		ray.dir.y = wolf->cam.dir.y + wolf->cam.plane.y * camera_x;
		intersect(wolf, &ray, step);
		if (wolf->cam.mode == WLF_MAP)
			draw_map(wolf, &ray, step);
		else
		{
			render_wolf(wolf, &ray, x, step);
			z_buffer[x] = ray.wall_dist;
		}
		x++;
	}
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->screen, 0, 0);
}
