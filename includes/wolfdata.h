/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolfdata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:19:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/15 04:09:20 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFDATA_H

#include <stdint.h>
# define SUCCESS	0
# define FAILURE 	-1

# define WOLFDATA_H
# define SWIN_X		1200
# define SWIN_Y		775
# define SIMG_X		1200
# define SIMG_Y		775
# define COL_WHITE	0x00FFFFFF
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
# define KEY_TAB	48
# define KEY_SPA	49
# define KEY_PGUP	116
# define KEY_PGDWN	121
# define KEY_LESS	69
# define KEY_PLUS	78

# define MAPWIDTH	24
# define MAPHEIGHT	24

# define TRUE		1
# define FALSE		0

# define WLF_RENDER	0
# define WLF_MAP	1

# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define TEX_MAX_NBR	16

# define TEX_ALL	0
# define TEX_NORTH	0
# define TEX_SOUTH	1
# define TEX_EAST	2
# define TEX_WEST	3

typedef struct		s_vector
{
	double	x;
	double	y;
}					t_vector;

typedef struct		s_camera
{
	t_vector	plane;
	t_vector	dir;
	t_vector	pos;
	int			mode;
}					t_camera;

typedef struct		s_ray
{
	t_vector	side_dist;
	t_vector	dir;
	double		wall_dist;
	int			tex_num;
	int			map[2];
	int			tex_x;
	int			side;
}					t_ray;

typedef struct		s_wall
{
	int8_t	tex_id[4];
	int8_t	crossable;
}					t_wall;

typedef struct		s_world
{
	int		width;
	int		height;
	int		center[2];
	int		spawn_x;
	int		spawn_y;
	char	**map;
	int		texture[TEX_MAX_NBR + 1][TEX_HEIGHT * TEX_WIDTH];
	t_wall	wall[256];
}					t_world;

#endif
