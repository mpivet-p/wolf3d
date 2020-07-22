/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_dist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:20:22 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/22 10:39:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	sort_sprites(int *sprite_order, double *sprite_dist, int len)
{
	int	tmp;
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (sprite_dist[sprite_order[i]] < sprite_dist[sprite_order[i + 1]])
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

void		get_sprites_dist(t_core *wolf, int *sprite_order)
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
