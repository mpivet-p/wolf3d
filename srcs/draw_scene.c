/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:47:25 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/14 14:56:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>

static void	prepare_draw_vert(
		int *start_end, t_ray *ray, double *step, double *tex_pos)
{
	double	line_height;

	line_height = (int)(SIMG_Y / ray->wall_dist);
	*step = 1.0 * TEX_HEIGHT / line_height;
	*tex_pos = (start_end[0] - SIMG_Y / 2 + line_height / 2) * *step;
}

void		draw_vert(t_core *wolf, int x, int *start_end, t_ray *ray)
{
	double	tex_pos;
	double	step;
	int		tex_y;
	int		color;
	int		i;

	i = (wolf->world.ceiling < 0) ? -1 : start_end[0];
	prepare_draw_vert(start_end, ray, &step, &tex_pos);
	while (++i < start_end[0])
		set_pixel(wolf->img, x, i, 0x7FC7E3);
	while (i < start_end[1])
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = wolf->world.texture[ray->tex_num][TEX_HEIGHT
			* tex_y + ray->tex_x];
		color = (ray->side == 1) ? (color >> 1) & 8355711 : color;
		set_pixel(wolf->img, x, i, color);
		i++;
	}
	if (wolf->world.floor < 0 && i--)
		while (++i < SIMG_Y)
			set_pixel(wolf->img, x, i, 0x401904);
}

int			get_texture_x(t_camera *cam, t_ray *ray)
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

double		render_wolf(t_core *wolf, t_ray *ray, int x, int *step)
{
	int			line_height;
	int			start_end[2];
	double		tmp;

	if (ray->side == 0)
		ray->wall_dist = (ray->map[0] - wolf->cam.pos.x
				+ (1 - step[0]) / 2) / ray->dir.x;
	else
		ray->wall_dist = (ray->map[1] - wolf->cam.pos.y
				+ (1 - step[1]) / 2) / ray->dir.y;
	line_height = (int)(SIMG_Y / ray->wall_dist);
	tmp = (line_height / -2) + (SIMG_Y / 2);
	start_end[0] = (tmp < 0) ? 0 : tmp;
	tmp = (line_height / 2) + (SIMG_Y / 2);
	start_end[1] = (tmp >= SIMG_Y) ? SIMG_Y - 1 : tmp;
	ray->tex_x = get_texture_x(&(wolf->cam), ray);
	ray->tex_num = wolf->world.map[ray->map[0]][ray->map[1]];
	ray->tex_num = get_tex_dir(&(wolf->world.wall[ray->tex_num]), ray);
	draw_vert(wolf, x, start_end, ray);
	return (ray->wall_dist);
}

int			draw_scene(t_core *wolf)
{
	double		camera_x;
	double		z_buffer[SIMG_X];
	t_ray		ray;
	int			step[2];
	int			x;

	x = -1;
	receive_players_pos(wolf);
	map_visualizer(wolf);
	floor_ceiling_casting(wolf);
	while (++x < SIMG_X)
	{
		ray.map[0] = (int)(wolf->cam.pos.x);
		ray.map[1] = (int)(wolf->cam.pos.y);
		camera_x = 2.0 * x / (double)SIMG_X - 1;
		ray.dir.x = wolf->cam.dir.x + wolf->cam.plane.x * camera_x;
		ray.dir.y = wolf->cam.dir.y + wolf->cam.plane.y * camera_x;
		intersect(wolf, &ray, step);
		draw_map(wolf, &ray, step);
		if (wolf->cam.mode != WLF_MAP)
			z_buffer[x] = render_wolf(wolf, &ray, x, step);
	}
	draw_sprites(wolf, z_buffer);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->screen, 0, 0);
	return (0);
}
