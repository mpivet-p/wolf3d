/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:00:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/31 15:00:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		test_shaders(int color, t_ray *ray)
{
	double	dist;
	float	coeff;
	int		r;
	int		g;
	int		b;

	dist = (ray->side == 0) ? ray->side_dist.x : ray->side_dist.y;
	coeff = (exp(dist / 3) -11) / -10;
	if (coeff < 0.0)
		coeff = 0;
	r = (color & 0xFF0000) >> 16;
	g = (color & 0x00FF00) >> 8;
	b = (color & 0x0000FF);
	return ((int)(r * coeff) << 16) | ((int)(g * coeff) << 8) | (int)(b * coeff);
}
