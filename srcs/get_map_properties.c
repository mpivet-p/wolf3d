#include "wolf.h"
#include "libft.h"
#include <limits.h>
#include <math.h>

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
	if (i < TEX_MAX && (array[i] = ft_strdup(key)) != NULL)
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
	if (ft_atol(properties[0], &wall_id) != 0 || wall_id > 255 || wall_id < 1)
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

int		register_new_texture(t_core *wolf, char **prp, char **files, int *tex_i)
{	
	int	tex_num;

	if ((tex_num = get_index(files, prp[1])) < 0)
		return (FAILURE);
	if (tex_num == *tex_i)
	{
		if (file_to_texture(wolf, &(wolf->world), prp[1], *tex_i) != 0)
			return (FAILURE);
		(*tex_i)++;
	}
	return (tex_num);
}

int8_t	set_floor_or_ceiling(t_core *wolf, char **prp, char **files, int *tex_i)
{
	int	tex_num;

	if ((tex_num = register_new_texture(wolf, prp, files, tex_i)) == FAILURE)
		return (FAILURE);
	if (prp[0][0] == 'f')
		wolf->world.floor = tex_num;
	else
		wolf->world.ceiling = tex_num;
	return (0);
}

int8_t	char_to_double(char *str, double *num)
{
	int64_t	tmp;
	int8_t	ret;
	char	**tab;

	ret = SUCCESS;
	if ((tab = ft_strsplit(str, '.')) == NULL)
		return (FAILURE);
	if (ft_tablen(tab) <= 2 && ft_atol(tab[0], &tmp) == SUCCESS && tmp < 100 && tmp >= 0)
	{
		*num = tmp;
		if (ft_tablen(tab) == 2 && ft_atol(tab[1], &tmp) == SUCCESS && tmp < INT_MAX)
		{
			//*num += tmp / (int)pow(10, log(tmp) + 1);
			num += 0;
		}
		else
			ret = FAILURE;
	}
	else
		ret = FAILURE;
	free_tab(&tab);
	return (ret);
	
}

int8_t	set_new_sprite(t_core *wolf, char **prp, char **files, int *tex_i)
{
	t_sprite	*sprt;
	int8_t		ret;
	int			tex_num;

	ret = SUCCESS;
	sprt = &(wolf->world.sprites[wolf->world.sprt_nbr]);
	if ((tex_num = register_new_texture(wolf, prp, files, tex_i)) == FAILURE)
		return (FAILURE);
	sprt->tex_id = tex_num;
	if (char_to_double(prp[2], &(sprt->x)) != SUCCESS)
		ret = FAILURE;
	if (ret == SUCCESS && char_to_double(prp[3], &(sprt->y)) != SUCCESS)
		ret = FAILURE;
	if (ret == SUCCESS)
		wolf->world.sprt_nbr++;
	return (ret);
}

int8_t	get_property_line(t_core *wolf, char **prp, char **files, int *tex_i)
{

	if ((ft_strcmp("floor", prp[0]) == 0 || ft_strcmp("ceiling", prp[0]) == 0)
			&& ft_tablen(prp) == 2)
		return (set_floor_or_ceiling(wolf, prp, files, tex_i));
	if (ft_strcmp(prp[0], "sprite") == 0 && ft_tablen(prp) == 4)
		return (set_new_sprite(wolf, prp, files, tex_i));
	return (set_new_wall(wolf, prp, files, tex_i));
}

int8_t	get_map_properties(t_core *wolf, int fd)
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
