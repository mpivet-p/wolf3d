/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:36:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/30 19:13:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	get_prite_dist(t_core *wolf, int *sprite_order)
{
	t_sprite	*sprt;
	t_vector	*pos;
	double		sprite_dist[SPRT_MAX];
	int	i;

	i = 0;
	pos = &(wolf->cam.pos);
	sprt = &(wolf->world.sprites);
	while (i < sprite_nbr)
	{
		sprite_order[i] = i;
		sprite_dist[i] = (pos.x - sprt[i]->x) * (pos.x - sprt[i]->x)
			+ (pos.y - sprt[i]->y) * (pos.y - sprt[i]->y);
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, )
}

static void	draw_vert_sprite(t_core *wolf, t_vector *sprite_screen
			, t_vector *sprite_dim, t_vector *transform, t_vecint *draw_end
			, t_vecint *draw_start, double *z_buffer, int8_t tex_id)
{
	t_vecint	tex;
	int			stripe;
	int			color;
	int			d;
	int			y;

	stripe = draw_start->x;
	while (stripe < draw_end->x)
	{
		tex.x = (256 * (stripe  - (-1 * sprite_dim->x / 2 + sprite_screen->x)) * TEX_WIDTH / sprite_dim->x) / 256;
		if (transform->y > 0 && stripe > 0 && stripe < SIMG_X && transform->y < z_buffer[stripe])
		{
			y = draw_start->y;
        	for (y < draw_end->y)
			{
        		d = (y) * 256 - h * 128 + sprite_dim.y * 128;
        		tex.y = ((d * TEX_HEIGHT) / sprite_dim.y) / 256;
        		color = wolf->world.sprite[tex_id][TEX_WIDTH * texY + texX];
				//On filtre la couleur noir (transparence)
        		if ((color & 0x00FFFFFF) != 0)
					set_pixel(wolf->img, stripe, y, color;
				y++;
        	}
		}
		stripe++;
	}
}

static void	machin(t_core *wolf, t_sprite *cur_sprite, double *correc)
{
	t_vecint	sprite_screen;
	t_vecint	sprite_dim;
	t_vecint	draw_start;
	t_vector	transform;
	t_vecint	draw_end;
	t_vector	sprite;

	//Calcul de la position relative
	sprite.x = cur_sprite.x - wolf->cam.pos.x;
	sprite.y = cur_sprite.y - wolf->cam.pos.y;
	//Application de la matrice inverse
	transform.x = correc * (wolf->cam.dir.y * sprite.x - wolf->cam.dir.x * sprite.y);
	transform.x = correc * (-1 * wolf->cam.plane.y * sprite.x - wolf->cam.plane.x * sprite.y);
	sprite_screen.x = (int)(SIMG_X / 2) * (1 + transform.x / transform.y);
	//Calcul de la hauteur du sprite
	sprite_dim.y = fabs((int)(SIMG_Y / transform.y));
	//Calcul du plus haut et du plus bas pixel a colorier
	draw_start.y = (-1 * sprite_dim.y) / 2 + SIMG_Y / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	draw_end.y = sprite_dim.y / 2 + SIMG_Y / 2;
	if (draw_end.y < 0)
		draw_end.y = SIMG_Y - 1;
	//Calcul de la largeur du sprite
	sprite_dim.x = fabs(SIMG_Y / tramsform.y);
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
		machin(wolf, wolf->world.sprite[i], );
		i++;
	}
}
