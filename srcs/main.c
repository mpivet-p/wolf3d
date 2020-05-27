/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/08/22 01:37:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"
#include <mlx.h>
#include <stdio.h>

void		init_core(t_core *wolf)
{
	int			tools[3];

	if (!(wolf->mlx = mlx_init()))
		quit_wolf(wolf);
	if (!(wolf->win = mlx_new_window(wolf->mlx, SWIN_X, SWIN_Y, "wolf3d par mpivet-p")))
		quit_wolf(wolf);
	if (!(wolf->screen = mlx_new_image(wolf->mlx, SIMG_X, SIMG_Y)))
		quit_wolf(wolf);
	if (!(wolf->img = mlx_get_data_addr(wolf->screen, &(tools[0]),
					&(tools[1]), &(tools[2]))))
		quit_wolf(wolf);
	mlx_hook(wolf->win, 17, 0, quit_wolf, wolf);
	mlx_hook(wolf->win, 2, 0, deal_key, wolf);
	mlx_hook(wolf->win, 4, 0, mouse_press, wolf);
}

static void	parse_wolf(int argc, char **argv, t_core *wolf)
{
	if (argc != 2 || ft_strlen(argv[1]) < 5)
	{
		ft_putstr_fd("usage: wolf3d map.txt\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	parse_wolf_map(argv[1], &(wolf->world));
}

//	debug_camera(&(wolf.cam));
//	debug_map(&(wolf.map));

int			main(int argc, char **argv)
{
	t_core	wolf;

	ft_bzero(&wolf, sizeof(t_core));
	parse_wolf(argc, argv, &wolf);
	init_camera(&(wolf.cam), &(wolf.world));
	init_core(&wolf);
	get_test_textures(&wolf);
	draw_scene(&wolf);
	mlx_loop(wolf.mlx);
	return (0);
}
