/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolfdata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:19:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2021/05/13 00:03:25 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFDATA_H
# define WOLFDATA_H

# include <stdint.h>
# include <netdb.h>

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

# ifdef __linux__
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_W		119
#  define KEY_A		97
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_Q		113
#  define KEY_E		101
#  define KEY_ESC	65307
#  define KEY_TAB	65289
#  define KEY_SPA	32
#  define KEY_PGUP	65365
#  define KEY_PGDWN	65366
#  define KEY_LESS	45
#  define KEY_PLUS	61
# else
#  define KEY_UP	126
#  define KEY_DOWN	125
#  define KEY_RIGHT	124
#  define KEY_LEFT	123
#  define KEY_W		13
#  define KEY_S		1
#  define KEY_A		0
#  define KEY_D		2
#  define KEY_Q		12
#  define KEY_E		14
#  define KEY_ESC	53
#  define KEY_TAB	48
#  define KEY_SPA	49
#  define KEY_PGUP	116
#  define KEY_PGDWN	121
#  define KEY_LESS	69
#  define KEY_PLUS	78
# endif

# define MAPWIDTH	24
# define MAPHEIGHT	24

# define TRUE		1
# define FALSE		0

# define WLF_RENDER	0
# define WLF_MAP	1

# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define TEX_MAX		16
# define SPRT_MAX		48

# define TEX_ALL	0
# define TEX_NORTH	0
# define TEX_SOUTH	1
# define TEX_EAST	2
# define TEX_WEST	3

# define MAX_PLAYERS	16
# define SRV_TRS_START	""
# define SRV_TRS_DONE	""
# ifndef SRV_BUFF
#  define SRV_BUFF		16
# endif

typedef struct		s_vector
{
	double	x;
	double	y;
}					t_vector;

typedef struct		s_vecint
{
	int	x;
	int	y;
}					t_vecint;

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
	char	gap_0[2];
}					t_wall;

typedef struct		s_sprite
{
	double	x;
	double	y;
	int8_t	tex_id;
	char	gap_0[3];
}					t_sprite;

typedef struct		s_sprtcalc
{
	t_vector	transform;
	t_vector	draw_start;
	t_vector	draw_end;
	int			sprite_size;
	int			sprite_screen_x;
}					t_sprtcalc;

typedef struct		s_world
{
	t_sprite	sprites[SPRT_MAX];
	int8_t		player_nbr;
	int8_t		sprt_nbr;
	int8_t		ceiling;
	int8_t		player;
	int8_t		spawn_x;
	int8_t		spawn_y;
	int8_t		height;
	int8_t		width;
	int8_t		floor;
	char		gap_0[1];
	char		**map;
	int			center[2];
	int			texture[TEX_MAX + 1][TEX_HEIGHT * TEX_WIDTH];
	t_wall		wall[256];
}					t_world;

#endif
