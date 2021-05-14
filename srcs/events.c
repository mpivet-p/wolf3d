/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:54:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/14 11:38:18 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <string.h>
#include <sys/select.h>

void	move_camera(t_core *wolf, int key)
{
	t_vector	new_pos;
	t_camera	*cam;
	t_world		*world;

	world = &(wolf->world);
	cam = &(wolf->cam);
	if (key == KEY_W || key == KEY_S)
		new_pos = cam->dir;
	else
		new_pos = rotate_vector(&(cam->dir), -M_PI / 2);
	new_pos.x *= (key == KEY_W || key == KEY_A) ? 0.10 : -0.10;
	new_pos.y *= (key == KEY_W || key == KEY_A) ? 0.10 : -0.10;
	if (cam->pos.x + new_pos.x < world->width && cam->pos.x + new_pos.x >= 0
		&& world->map[(int)(cam->pos.x + new_pos.x)][(int)(cam->pos.y)] == 0)
		cam->pos.x += new_pos.x;
	if (cam->pos.y + new_pos.y < world->height && cam->pos.y + new_pos.y >= 0
		&& world->map[(int)(cam->pos.x)][(int)(cam->pos.y + new_pos.y)] == 0)
		cam->pos.y += new_pos.y;
	if (wolf->socket != -1)
		send_pos_to_server(wolf);
}

void	rotate_camera(t_core *wolf, int key)
{
	double		angle;

	angle = (key == KEY_RIGHT) ? M_PI / 40 : -M_PI / 40;
	wolf->cam.dir = rotate_vector(&(wolf->cam.dir), angle);
	wolf->cam.plane = rotate_vector(&(wolf->cam.plane), angle);
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
