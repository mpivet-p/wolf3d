/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolfdata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:19:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/08/22 01:42:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFDATA_H
# define WOLFDATA_H
# define SWIN_X		1200
# define SWIN_Y		775
# define SIMG_X		1200
# define SIMG_Y		775
# define COL_WHITE	0xFFFFFF
# define COL_RED	0xF54611
# define COL_GREEN	0x2CA338
# define COL_BLUE	0x0589F5
# define COL_YELLO	0xF5A511
# define COL_PURPLE	0xC017E6
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_RIGHT	124
# define KEY_LEFT	123
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2
# define KEY_Q		12
# define KEY_E		14
# define KEY_ESC	53
# define KEY_SPA	49
# define KEY_SPA	49
# define KEY_PGUP	116
# define KEY_PGDWN	121
# define KEY_LESS	69
# define KEY_PLUS	78

# define MAPWIDTH	24
# define MAPHEIGHT	24

typedef struct		s_vector
{
	double	x;
	double	y;
}					t_vector;

typedef struct		s_camera
{
	t_vector	dir;
	t_vector	pos;
	t_vector	plane;
}					t_camera;

typedef struct		s_map
{
	int		width;
	int		height;
	int		spawn_x;
	int		spawn_y;
	char	**map;
}					t_map;

#endif
