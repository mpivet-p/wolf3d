/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_walls_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:57:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/15 02:32:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int8_t	get_index(char **array, char *key)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], key) == 0)
			return (i);
		i++;
	}
	if (i < TEX_MAX_NBR && (array[i] = ft_strdup(key)) != NULL)
		return (i);
	return (-1);
}

static int	set_new_wall(t_core *wolf, char **properties, char **files, int *tex_i)
{
	int64_t	wall_id;
	int		tex_id;
	int		len;
	int		i;

	tex_id = 0;
	i = 0;
	len = ft_tablen(properties);
	if (ft_atol(properties[0], &wall_id) != 0)
		return (1);
	while (++i < len)
	{
		if (i == len - 1 && (i > 1 || i > 5) && ft_strcmp(properties[i], "true") == 0)
		{
			wolf->world.wall[wall_id].crossable = TRUE;
			break ;
		}
		if ((tex_id = get_index(files, properties[i])) < 0)
			return (1);
		wolf->world.wall[wall_id].tex_id[i - 1] = tex_id + 1;
		if (tex_id == *tex_i)
		{
			if (file_to_texture(wolf, &(wolf->world), properties[i], *tex_i) != 0)
				return (1);
			(*tex_i)++;
		}
	}
	return (0);
}

int8_t	get_walls_properties(t_core *wolf, int fd)
{
	char	**files;
	char	**array;
	char	*line;
	int		tex_i;

	files = (char**)ft_memalloc(sizeof(char**) * (TEX_MAX_NBR + 1));
	tex_i = 0;
	while (tex_i != -1 && get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) != 0 && line[0] != '#')
		{
			array = ft_strsplit(line, ':');
			if (!array || set_new_wall(wolf, array, files, &tex_i) != 0)
			{
				ft_putstr_fd("wolf3d: parsing properties error\n", STDERR_FILENO);
				tex_i = -1;
			}
			ft_tabdel(&array);
		}
		ft_strdel(&line);
	}
	ft_tabdel(&files);
	return ((tex_i != -1) ? 0 : 1);
}
