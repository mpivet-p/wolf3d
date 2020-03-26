/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 03:55:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/08 00:02:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "wolfdata.h"

typedef struct	s_core
{
	void		*mlx;
	void		*win;
	void		*screen;
	char		*img;
	double		time;
	double		oldtime;
	t_map		map;
	t_camera	cam;
}				t_core;

/*
** ============================================================================
**	EVENTS.....................................................................
** ============================================================================
*/

int				mouse_press(int button, int x, int y, t_core *wolf);
int				mouse_move(int x, int y, t_core *wolf);
int				deal_key(int key, t_core *wolf);

/*
** ============================================================================
**	TOOLS......................................................................
** ============================================================================
*/

void			set_pixel(char *image, int x, int y, int color);
int				quit_wolf(void *wolf);
void			init_camera(t_camera *cam, t_map *map);
int				print_and_quit(char *error);
void			parse_wolf_map(char *filename, t_map *map);

/*
** ============================================================================
**	DEBUG......................................................................
** ============================================================================
*/

void			debug_camera(t_camera *cam);
void			debug_map(t_map *map);

#endif
