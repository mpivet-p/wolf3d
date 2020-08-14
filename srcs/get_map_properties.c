/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:40:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/14 14:58:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int8_t	set_floor_or_ceiling(
		t_core *wolf, char **prp, char **files, int *tex_i)
{
	int	tex_num;

	if ((tex_num = register_new_texture(wolf, prp, files, tex_i)) == FAILURE)
		return (FAILURE);
	if (prp[0][0] == 'f')
		wolf->world.floor = tex_num;
	else
		wolf->world.ceiling = tex_num;
	return (SUCCESS);
}

static int8_t	set_player_texture(
		t_core *wolf, char **prp, char **files, int *tex_i)
{
	int	tex_num;

	if ((tex_num = register_new_texture(wolf, prp, files, tex_i)) == FAILURE)
		return (FAILURE);
	wolf->world.player = tex_num;
	return (SUCCESS);
}

static int8_t	get_property_line(
		t_core *wolf, char **prp, char **files, int *tex_i)
{
	if ((ft_strcmp("floor", prp[0]) == 0 || ft_strcmp("ceiling", prp[0]) == 0)
			&& ft_tablen(prp) == 2)
		return (set_floor_or_ceiling(wolf, prp, files, tex_i));
	if (ft_strcmp("player", prp[0]) == 0 && ft_tablen(prp) == 2)
		return (set_player_texture(wolf, prp, files, tex_i));
	if (ft_strcmp(prp[0], "sprite") == 0 && ft_tablen(prp) == 4)
		return (set_new_sprite(wolf, prp, files, tex_i));
	return (set_new_wall(wolf, prp, files, tex_i));
}

int8_t			get_map_properties(t_core *wolf, int fd)
{
	char	**files;
	char	**prp;
	char	*line;
	int		tex_i;

	files = (char**)ft_memalloc(sizeof(char**) * (TEX_MAX + 1));
	tex_i = 0;
	while (tex_i != -1 && get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) != 0 && line[0] != '#')
		{
			prp = ft_strsplit(line, ':');
			if (!prp || get_property_line(wolf, prp, files, &tex_i) != 0)
			{
				ft_putstr_fd("wolf3d: parsing properties error: "
				, STDERR_FILENO);
				ft_putendl_fd(line, STDERR_FILENO);
				tex_i = -1;
			}
			ft_tabdel(&prp);
		}
		ft_strdel(&line);
	}
	ft_tabdel(&files);
	return ((tex_i != -1) ? 0 : 1);
}
