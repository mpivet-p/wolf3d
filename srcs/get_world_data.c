/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_world_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 14:35:49 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/13 00:02:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int	get_world_data(int fd, int *array)
{
	char	*line;

	line = NULL;
	get_next_line(fd, &line);
	if (ft_strlen(line) != 5 || line[2] != 'x')
		return (1);
	if ((array[0] = ft_atoi(line)) <= 0
			|| (array[1] = ft_atoi(line + 3)) <= 0)
		return (1);
	ft_strdel(&line);
	return (0);
}

void		get_world_dimensions(t_world *world, int *array, int fd)
{
	if (get_world_data(fd, array) != 0)
		print_and_quit("wolf3d: parse error: line 1\n");
	world->width = array[0];
	world->height = array[1];
}

void		get_spawn_coords(t_world *world, int *array, int fd)
{
	if (get_world_data(fd, array) != 0)
		print_and_quit("wolf3d: parse error: line 2\n");
	world->spawn_x = array[0];
	world->spawn_y = array[1];
}
