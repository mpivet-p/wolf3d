/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:41:57 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:41:59 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

t_vector	get_delta_dist(t_vector *raydir)
{
	t_vector	delta_dist;

	if (raydir->y == 0)
		delta_dist.x = 0;
	else
		delta_dist.x = (raydir->x == 0) ? 1 : fabs(1.0 / raydir->x);
	if (raydir->x == 0)
		delta_dist.y = 0;
	else
		delta_dist.y = (raydir->y == 0) ? 1 : fabs(1.0 / raydir->y);
	return (delta_dist);
}
