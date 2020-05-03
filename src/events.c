/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:54:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/08/22 05:23:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include <string.h>

void	move_camera(t_core *wolf, int key)
{
	t_camera	*cam;
	t_world		*world;

	world = &(wolf->world);
	cam = &(wolf->cam);
	if (key == KEY_W && cam->pos.y - 0.25 > 0
		&& world->map[(int)(cam->pos.x)][(int)(cam->pos.y - 0.25)] == 0)
		cam->pos.y -= 0.25;
	else if (key == KEY_S && cam->pos.y + 0.25 < world->height
		&& world->map[(int)(cam->pos.x)][(int)(cam->pos.y + 0.25)] == 0)
		cam->pos.y += 0.25;
	else if (key == KEY_A && cam->pos.x - 0.25 > 0
		&& world->map[(int)(cam->pos.x - 0.25)][(int)(cam->pos.y)] == 0)
		cam->pos.x -= 0.25;
	else if (key == KEY_D && cam->pos.x + 0.25 < world->width
		&& world->map[(int)(cam->pos.x + 0.25)][(int)(cam->pos.y)] == 0)
		cam->pos.x += 0.25;
	map_visualizer(wolf);
	draw_scene(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->screen, 0, 0);
}

void	rotate_camera(t_core *wolf, int key)
{
	t_vector	save;
	double		angle;

	angle = (key == KEY_LEFT) ? -0.2 : 0.2;
	save = wolf->cam.dir;
	wolf->cam.dir.x = (save.x * cos(angle)) - (sin(angle) * save.y);
	wolf->cam.dir.y = (save.x * sin(angle)) + (cos(angle) * save.y);
	unit(&(wolf->cam.dir));
	map_visualizer(wolf);
	draw_scene(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->screen, 0, 0);
}

int		deal_key(int key, t_core *wolf)
{
	if (key == KEY_ESC)
		quit_wolf(wolf);
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
		move_camera(wolf, key);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_camera(wolf, key);
	return (key);
}

int		mouse_press(int button, int x, int y, t_core *mlx)
{
	(void)x;
	(void)y;
	(void)mlx;
	return (button);
}

int		mouse_move(int x, int y, t_core *mlx)
{
	(void)x;
	(void)y;
	(void)mlx;
	return (0);
}
