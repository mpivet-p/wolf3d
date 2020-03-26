//HEADER

#include "wolf.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>

static int	get_map_data(int fd, int *array)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	get_next_line(fd, &line);
	if (ft_strlen(line) != 5 || line[2] != 'x')
		return (1);
	if ((array[0] = ft_atoi(line)) <= 0 || (array[1] = ft_atoi(line + 3)) <= 0)
		return (1);
	ft_strdel(&line);
	return (0);
}

static int	check_line(char *str, t_map *map)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != ' ' || str[i + 1] < '0' || str[i + 1] > '9')
				return (1);
			else
				count++;
		}
		i++;
	}
	if ((int)count + 1 != map->width)
		return (1);
	return (0);
}

static int	get_map_line(char *str, t_map *map, int line)
{
	long long	tmp;
	size_t		len;
	size_t		i;
	char		**tab;

	i = 0;
	len = ft_strlen(str);
	if (check_line(str, map) != 0)
		return (1);
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		if (map->map[i] == NULL)
			map->map[i] = ft_memalloc(sizeof(char*) * (map->height + 1));
		tmp = 0;
		if (ft_atol(tab[i], &tmp) != 0 || tmp > 255 || tmp < 0)
			return (-1);
		map->map[i][line] = tmp & 0xFF;
		i++;
	}
	return (0);
}

static int	get_wolf_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (i < map->height && get_next_line(fd, &line) > 0)
	{
		if (get_map_line(line, map, i) != 0)
		{
			ft_putstr_fd("wolf3d: line ", STDERR_FILENO);
			ft_putnbr_fd(i + 3, STDERR_FILENO);
			ft_putstr_fd(": invalid input\n", STDERR_FILENO);
			return (1);
		}
		ft_strdel(&line);
		i++;
	}
	if (i != map->height || get_next_line(fd, &line) > 0)
	{
		ft_putstr_fd("wolf3d: invalid map size\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void		parse_wolf_map(char *filename, t_map *map)
{
	int	fd;
	int	array[2];

	if ((fd = open(filename, O_RDONLY)) < 0)
		print_and_quit("wolf3d: invalid file\n");
	if (get_map_data(fd, array) != 0)
		print_and_quit("wolf3d: parse error: line 1\n");
	map->width = array[0];
	map->height = array[1];
	if (get_map_data(fd, array) != 0)
		print_and_quit("wolf3d: parse error: line 2\n");
	map->spawn_x = array[0];
	map->spawn_y = array[1];
	if ((map->map = ft_memalloc(sizeof(char **) * (map->height + 1))) == NULL)
		print_and_quit("wolf3d: malloc error\n");
	if (get_wolf_map(fd, map) != 0)
	{
		ft_tabdel(&(map->map));
		exit(EXIT_FAILURE);
	}
}
