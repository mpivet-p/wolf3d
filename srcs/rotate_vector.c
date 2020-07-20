/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:47:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:47:09 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

t_vector	rotate_vector(t_vector *vector, double angle)
{
	t_vector	new_vec;

	new_vec.x = (vector->x * cos(angle)) - (sin(angle) * vector->y);
	new_vec.y = (vector->x * sin(angle)) + (cos(angle) * vector->y);
	return (new_vec);
}
