/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:36:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/23 15:48:32 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	sort_sprites(t_core *wolf)
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
}

void	draw_sprites()
{
	
}
