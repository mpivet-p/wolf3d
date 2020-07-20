/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:36:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 16:00:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	sort_sprites(int *sprite_order, double *sprite_dist, int len)
{
	int	tmp;
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (sprite_dist[sprite_order[i]] > sprite_dist[sprite_order[i + 1]])
		{
			tmp = sprite_order[i];
			sprite_order[i] = sprite_order[i + 1];
			sprite_order[i + 1] = tmp;
			i = 0;
			continue ;
		}
		i++;
	}
}

static void	get_sprite_dist(t_core *wolf, int *sprite_order)
{
	t_sprite	*sprt;
	t_vector	*pos;
	double		sprite_dist[SPRT_MAX];
	int			i;

	i = 0;
	pos = &(wolf->cam.pos);
	sprt = wolf->world.sprites;
	while (i < wolf->world.sprt_nbr)
	{
		sprite_order[i] = i;
		sprite_dist[i] = (wolf->cam.pos.x - sprt[i].x)
			* (wolf->cam.pos.x - sprt[i].x)
			+ (wolf->cam.pos.y - sprt[i].y) * (wolf->cam.pos.y - sprt[i].y);
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, wolf->world.sprt_nbr);
}

static void	draw_sprite_vert(t_core *wolf, int sprite_screen_x
			, int sprite_size, t_vector *transform, t_vecint *draw_end
			, t_vecint *draw_start, double *z_buffer, int8_t tex_id)
{
	t_vecint	tex;
	int			x;
	int			color;
	int			d;
	int			y;

	x = draw_start->x;
	while (x < draw_end->x)
	{
		tex.x = (256 * (x - (sprite_screen_x - sprite_size / 2))
				* TEX_WIDTH / sprite_size) / 256;
		if (transform->y > 0 && x > 0
				&& x < SIMG_X && transform->y < z_buffer[x])
		{
			y = draw_start->y;
			while (y < draw_end->y)
			{
				d = y * 256 - SIMG_Y * 128 + sprite_size * 128;
				tex.y = ((d * TEX_HEIGHT) / sprite_size) / 256;
				color = wolf->world.texture[tex_id][TEX_WIDTH * tex.y + tex.x];
				if ((color & 0x00FFFFFF) != 0)
					set_pixel(wolf->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

static void	prepare_sprites(
		t_core *wolf, t_sprite *curr_sprite, double correc, double *z_buffer)
{
	t_vecint	draw_start;
	t_vector	transform;
	t_vecint	draw_end;
	t_vector	sprite;
	int			sprite_screen_x;
	int			sprite_size;

	sprite.x = curr_sprite->x - wolf->cam.pos.x;
	sprite.y = curr_sprite->y - wolf->cam.pos.y;
	transform.x = correc
		* (wolf->cam.dir.y * sprite.x - wolf->cam.dir.x * sprite.y);
	transform.y = correc
		* (wolf->cam.plane.x * sprite.y - wolf->cam.plane.y * sprite.x);
	sprite_screen_x = (int)((SIMG_X / 2) * (1 + transform.x / transform.y));
	sprite_size = (int)fabs(SIMG_Y / transform.y);
	draw_start.y = SIMG_Y / 2 - sprite_size / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	draw_end.y = sprite_size / 2 + SIMG_Y / 2;
	if (draw_end.y < 0 || draw_end.y > SIMG_Y)
		draw_end.y = SIMG_Y - 1;
	sprite_size = (int)fabs(SIMG_Y / transform.y);
	draw_start.x = sprite_screen_x - sprite_size / 2;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_end.x = sprite_size / 2 + sprite_screen_x;
	if (draw_end.x >= SIMG_X)
		draw_end.x = SIMG_X - 1;
	draw_sprite_vert(wolf, sprite_screen_x, sprite_size, &transform, &draw_end, &draw_start, z_buffer, curr_sprite->tex_id);
}

void		draw_sprites(t_core *wolf, double *z_buffer)
{
	double	correction;
	int		sprite_order[SPRT_MAX];
	int		i;

	i = 0;
	correction = 1.0 / (wolf->cam.plane.x * wolf->cam.dir.y
				- wolf->cam.dir.x * wolf->cam.plane.y);
	get_sprite_dist(wolf, sprite_order);
	while (i < wolf->world.sprt_nbr)
	{
		prepare_sprites(wolf, &(wolf->world.sprites[i]), correction, z_buffer);
		i++;
	}
}
