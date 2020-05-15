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
#include <string.h>

void	move_camera(t_core *wolf, int key)
{
	t_camera	*cam;
	t_world		*world;

	world = &(wolf->world);
	cam = &(wolf->cam);
	if (key == KEY_W && cam->pos.y - 0.50 > 0
		&& world->map[(int)(cam->pos.x)][(int)(cam->pos.y - 1)] == 0)
		cam->pos.y -= 0.50;
	else if (key == KEY_S && cam->pos.y + 0.50 < world->height
		&& world->map[(int)(cam->pos.x)][(int)(cam->pos.y + 0.50)] == 0)
		cam->pos.y += 0.50;
	else if (key == KEY_A && cam->pos.x - 0.50 > 0
		&& world->map[(int)(cam->pos.x - 1)][(int)(cam->pos.y)] == 0)
		cam->pos.x -= 0.50;
	else if (key == KEY_D && cam->pos.x + 0.50 < world->width
		&& world->map[(int)(cam->pos.x + 0.50)][(int)(cam->pos.y)] == 0)
		cam->pos.x += 0.50;
}

void	rotate_camera(t_core *wolf, int key)
{
	t_vector	save;
	double		angle;

	angle = (key == KEY_LEFT) ? -0.1 : 0.1;
	save = wolf->cam.dir;
	wolf->cam.dir.x = (save.x * cos(angle)) - (sin(angle) * save.y);
	wolf->cam.dir.y = (save.x * sin(angle)) + (cos(angle) * save.y);
	unit(&(wolf->cam.dir));
}

int		deal_key(int key, t_core *wolf)
{
	if (key == KEY_ESC)
		quit_wolf(wolf);
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
		move_camera(wolf, key);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_camera(wolf, key);
	else if (key == KEY_TAB)
		wolf->cam.mode ^= WLF_MAP;
	else
		return (key);
	draw_scene(wolf);
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
