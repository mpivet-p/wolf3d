/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:49:56 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/21 15:28:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int8_t	set_wall_crossable(
		t_core *wolf, char **prp, int i, int64_t wall_id)
{
	int	len;

	len = ft_tablen(prp);
	if (i == len - 1 && (i > 1 || i > 5) && ft_strcmp(prp[i], "true") == 0)
	{
		wolf->world.wall[wall_id].crossable = TRUE;
		return (1);
	}
	return (0);
}

int				set_new_wall(t_core *wolf, char **prp, char **files, int *tex_i)
{
	int64_t	wall_id;
	int		tex_id;
	int		i;

	tex_id = 0;
	i = 0;
	if (ft_atol(prp[0], &wall_id) != 0 || wall_id > 255 || wall_id < 1)
		return (1);
	while (prp[++i] && set_wall_crossable(wolf, prp, i, wall_id) != FAILURE)
	{
		if ((tex_id = get_index(files, prp[i])) < 0)
			return (1);
		wolf->world.wall[wall_id].tex_id[i - 1] = tex_id + 1;
		if (tex_id == *tex_i)
		{
			if (file_to_texture(wolf, &(wolf->world), prp[i], *tex_i) != 0)
				return (1);
			(*tex_i)++;
		}
	}
	return (0);
}
