/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/27 14:06:28 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"
#include <mlx.h>
#include <stdio.h>

static void	init_core(t_core *wolf)
{
	int			tools[3];

	if (!(wolf->win = mlx_new_window(
					wolf->mlx, SWIN_X, SWIN_Y, "wolf3d par mpivet-p")))
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

static void	print_usage(void)
{
	ft_putstr_fd("usage: wolf3d [file] [-M adress]\n", STDERR_FILENO);
}

static void	parse_args(int argc, char **argv)
{
	if (argc < 2)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (argc == 2)
		return ;
	if (argc == 4 && ft_strcmp("-M", argv[2]) == 0)
	{
		connect_to_server(argv[3]);
		dprintf(STDERR_FILENO, "Connection...\n");
	}
	else
	{
		print_usage();
		exit(FAILURE);
	}
}

int			main(int argc, char **argv)
{
	t_core	wolf;

	ft_bzero(&wolf, sizeof(t_core));
	parse_args(argc, argv);
	if (!(wolf.mlx = mlx_init()))
		quit_wolf(&wolf);
	parse_wolf_map(&wolf, &(wolf.world), argv[1]);
	init_camera(&(wolf.cam), &(wolf.world));
	init_core(&wolf);
	get_test_textures(&wolf);
	draw_scene(&wolf);
	mlx_loop(wolf.mlx);
	return (0);
}
