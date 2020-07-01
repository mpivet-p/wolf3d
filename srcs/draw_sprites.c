/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:36:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/01 19:59:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

static void	get_sprite_dist(t_core *wolf, int *sprite_order)
{
	t_sprite	*sprt;
	t_vector	*pos;
	double		sprite_dist[SPRT_MAX];
	int	i;

	i = 0;
	pos = &(wolf->cam.pos);
	sprt = (wolf->world.sprites);
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

static void	draw_vert_sprite(t_core *wolf, t_vector *sprite_screen
			, t_vector *sprite_dim, t_vector *transform, t_vecint *draw_end
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
		tex.x = (256 * (x  - (-1 * sprite_dim->x / 2 + sprite_screen->x)) * TEX_WIDTH / sprite_dim->x) / 256;
		if (transform->y > 0 && x > 0 && x < SIMG_X && transform->y < z_buffer[x])
		{
			y = draw_start->y;
        	while (y < draw_end->y)
			{
        		d = (y) * 256 - SIMG_Y * 128 + sprite_dim->y * 128;
        		tex.y = ((d * TEX_HEIGHT) / sprite_dim->y) / 256;
        		color = wolf->world.sprt_tex[tex_id][TEX_WIDTH * tex.y + tex.x];
        		if ((color & 0x00FFFFFF) != 0)
					set_pixel(wolf->img, x, y, color);
				y++;
        	}
		}
		x++;
	}
}

static void	prepare_sprites(t_core *wolf, t_sprite *curr_sprite, double correc)
{
	t_vecint	sprite_screen;
	t_vecint	sprite_dim;
	t_vecint	draw_start;
	t_vector	transform;
	t_vecint	draw_end;
	t_vector	sprite;

	sprite.x = curr_sprite->x - wolf->cam.pos.x;
	sprite.y = curr_sprite->y - wolf->cam.pos.y;
	transform.x = correc * (wolf->cam.dir.y * sprite.x - wolf->cam.dir.x * sprite.y);
	transform.x = correc * (-1 * wolf->cam.plane.y * sprite.x - wolf->cam.plane.x * sprite.y);
	sprite_screen.x = (int)(SIMG_X / 2) * (1 + transform.x / transform.y);
	sprite_dim.y = (int)fabs(SIMG_Y / transform.y);
	draw_start.y = (-1 * sprite_dim.y) / 2 + SIMG_Y / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	draw_end.y = sprite_dim.y / 2 + SIMG_Y / 2;
	if (draw_end.y < 0)
		draw_end.y = SIMG_Y - 1;
	sprite_dim.x = fabs(SIMG_Y / transform.y);
	draw_start.x = (-1 * sprite_dim.x) / 2 + sprite_screen.x;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_start.x = sprite_dim.x / 2 + sprite_screen.x;
	if (draw_end.x < 0)
		draw_end.x = SIMG_X - 1;
	draw_sprite_vert();
}


void	draw_sprites(t_core *wolf)
{
	double	correction;
	int		sprite_order[SPRT_MAX];
	int		i;

	i = 0;
	correction = 1.0 / (wolf->cam.plane.x * wolf->cam.dir.y - wolf->cam.dir.x * wolf->cam.plane.y);
	get_sprite_dist(wolf, sprite_order);
	while (i < wolf->world.sprt_nbr)
	{
		prepare_sprites(wolf, &(wolf->world.sprites[i]), correction);
		i++;
	}
}
