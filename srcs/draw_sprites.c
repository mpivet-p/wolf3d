/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:36:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/22 10:36:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	draw_sprite_vert(
		t_core *wolf, t_sprtcalc *sprt, double *z_buffer, int8_t tex_id)
{
	t_vecint	tex;
	int			x;
	int			color;
	int			d;
	int			y;

	x = sprt->draw_start.x - 1;
	while (++x < sprt->draw_end.x)
	{
		tex.x = (256 * (x - (sprt->sprite_screen_x - sprt->sprite_size / 2))
				* TEX_WIDTH / sprt->sprite_size) / 256;
		if (sprt->transform.y > 0 && x > 0
				&& x < SIMG_X && sprt->transform.y < z_buffer[x])
		{
			y = sprt->draw_start.y - 1;
			while (++y < sprt->draw_end.y)
			{
				d = y * 256 - SIMG_Y * 128 + sprt->sprite_size * 128;
				tex.y = ((d * TEX_HEIGHT) / sprt->sprite_size) / 256;
				color = wolf->world.texture[tex_id][TEX_WIDTH * tex.y + tex.x];
				if ((color & 0x00FFFFFF) != 0)
					set_pixel(wolf->img, x, y, color);
			}
		}
	}
}

static void	calc_start_end(t_sprtcalc *sprt)
{
	sprt->draw_start.y = SIMG_Y / 2 - sprt->sprite_size / 2;
	if (sprt->draw_start.y < 0)
		sprt->draw_start.y = 0;
	sprt->draw_end.y = sprt->sprite_size / 2 + SIMG_Y / 2;
	if (sprt->draw_end.y < 0 || sprt->draw_end.y > SIMG_Y)
		sprt->draw_end.y = SIMG_Y - 1;
	sprt->sprite_size = (int)fabs(SIMG_Y / sprt->transform.y);
	sprt->draw_start.x = sprt->sprite_screen_x - sprt->sprite_size / 2;
	if (sprt->draw_start.x < 0)
		sprt->draw_start.x = 0;
	sprt->draw_end.x = sprt->sprite_size / 2 + sprt->sprite_screen_x;
	if (sprt->draw_end.x >= SIMG_X)
		sprt->draw_end.x = SIMG_X - 1;
}

static void	prepare_sprites(
		t_core *wolf, t_sprite *curr_sprite, double correc, double *z_buffer)
{
	t_sprtcalc	sprt;
	t_vector	sprite;

	sprite.x = curr_sprite->x - wolf->cam.pos.x;
	sprite.y = curr_sprite->y - wolf->cam.pos.y;
	sprt.transform.x = correc
		* (wolf->cam.dir.y * sprite.x - wolf->cam.dir.x * sprite.y);
	sprt.transform.y = correc
		* (wolf->cam.plane.x * sprite.y - wolf->cam.plane.y * sprite.x);
	sprt.sprite_screen_x = (int)((SIMG_X / 2)
			* (1 + sprt.transform.x / sprt.transform.y));
	sprt.sprite_size = (int)fabs(SIMG_Y / sprt.transform.y);
	calc_start_end(&sprt);
	draw_sprite_vert(wolf, &sprt, z_buffer, curr_sprite->tex_id);
}

void		draw_sprites(t_core *wolf, double *z_buffer)
{
	double	correction;
	int		sprite_order[SPRT_MAX];
	int		i;

	i = 0;
	if (wolf->cam.mode == WLF_MAP)
		return ;
	correction = 1.0 / (wolf->cam.plane.x * wolf->cam.dir.y
				- wolf->cam.dir.x * wolf->cam.plane.y);
	get_sprites_dist(wolf, sprite_order);
	while (i < wolf->world.sprt_nbr)
	{
		prepare_sprites(wolf, &(wolf->world.sprites[sprite_order[i]])
				, correction, z_buffer);
		i++;
	}
}
