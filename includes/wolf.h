/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 03:55:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/17 04:36:19 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include "wolfdata.h"
#include <stdio.h>
#include <stdint.h>

typedef struct	s_core
{
	void		*mlx;
	void		*win;
	void		*screen;
	char		*img;
	double		time;
	double		oldtime;
	t_world		world;
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

void			center_map(int width, int height, int sq_size, int8_t *shift);
t_vector		rotate_vector(t_vector *vector, double angle);
t_vector		set_vec(double x, double y);
void			set_pixel(char *image, int x, int y, int color);
int				quit_wolf(void *wolf);
void			init_camera(t_camera *cam, t_world *world);
int				print_and_quit(char *error);
void			map_visualizer(t_core *wolf);
void			bresenham(t_core *wolf, t_vector one, t_vector two, int color);
void			draw_ray(t_core *wolf, t_vector ray, int color);
void			unit(t_vector *dir);
void			draw_square(t_core *wolf, int x, int y, int color);

void			draw_map(t_core *wolf, t_ray *ray, int *step);
t_vector		get_side_dist(t_camera *cam, t_ray *ray,
					t_vector *delta_dist, int *step);
t_vector		get_delta_dist(t_vector *raydir);

/*
** ============================================================================
**	PARSING....................................................................
** ============================================================================
*/

void			parse_wolf_map(t_core *wolf, t_world *world, char *filename);
void			get_test_textures(t_core *wolf);
int8_t			file_to_texture(
		t_core *wolf, t_world *world, char *file, int tex_i);
int8_t			get_walls_properties(t_core *wolf, int fd);

/*
** ============================================================================
**	DEBUG......................................................................
** ============================================================================
*/

void			debug_camera(t_camera *cam);
void			debug_map(t_world *world);

/*
** ============================================================================
**	RENDER.....................................................................
** ============================================================================
*/

void	draw_scene(t_core *wolf);
void	floor_ceiling_casting(t_core *wolf);
void	draw_sprites(t_core *wolf, double *z_buffer);

#endif
