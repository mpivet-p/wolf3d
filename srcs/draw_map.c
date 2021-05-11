/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:42:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/11 11:55:51 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <unistd.h>

void	draw_map(t_core *wolf, t_ray *ray)
{
	if (wolf->cam.mode != WLF_MAP)
		return ;
	draw_square(wolf, ray->map[0], ray->map[1], 0x0000CC);
}
