/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/18 14:27:43 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "math_utils.h"
// # include "assert.h"

# define WIN_X	1000
# define WIN_Y	1000

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE
}	t_type;

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
	float	brightness;
}	t_rgb;

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_inter
{
	double	t;
	t_rgb	color;
	t_type	*obj;
}	t_inter;

typedef struct s_base
{
	t_vect	h_normal;
	t_vect	v_normal;
}	t_base;

typedef struct s_screen
{
	t_vect	pix_x;
	t_vect	pix_y;
	t_vect	center;
}	t_screen;

typedef struct s_cam
{
	t_vect		position;
	t_vect		direction_n;
	float		fov;

	t_base		base;
	t_screen	screen;
}	t_cam;

typedef struct s_ambient
{
	t_rgb	color;
}	t_ambient;

typedef struct light
{
	t_vect	position;
	t_rgb	color;
}	t_light;

typedef struct s_sp
{
	t_type	type;
	t_vect	center;
	float	diameter;
	float	radius;
	t_rgb	color;
}	t_sp;

typedef struct s_pl
{
	t_type	type;
	t_vect	point;
	t_vect	normal_n;
	t_rgb	color;

	double	d;
}	t_pl;

typedef struct s_cy
{
	t_type	type;
	t_vect	center;
	t_vect	axis_n;
	float	diameter;
	float	height;

	float	radius;
	float	semi_height;
	t_vect	top;
	t_vect	bottom;
	double	dt;
	double	db;
	t_rgb	color;
}	t_cy;

typedef struct s_rt
{
	t_mlx		mlx;
	t_cam		camera;
	t_light		light;
	t_ambient	ambiant;
	int			nb_object;
	t_type		*object[20];
	int			menu;
}	t_rt;

void	check_args(int argc);

int		fill_vec(char *str, t_vect *vec);
int		fill_rgb(char *str, t_rgb *color);

int		get_cam_info(char **tok, t_rt *rt);
int		get_light_info(char **tok, t_rt *rt);
int		get_ambient_info(char **tok, t_rt *rt);
int		get_sphere_info(char **tok, t_rt *rt);
int		get_cylinder_info(char **tok, t_rt *rt);
int		get_plane_info(char **tok, t_rt *rt);

void	set_cam_base(t_cam *cam);

void	throwing_rays_through_the_wide_universe(t_rt *rt);

void	inter_sphere(t_rt *rt, t_vect ray, t_sp *sp, t_inter *inter, t_vect start);
void	inter_cylinder(t_rt *rt, t_vect ray, t_cy*cy, t_inter *inter, t_vect start);
void	inter_plane(t_rt *rt, t_vect ray, t_pl *pl, t_inter *inter, t_vect start);

void	print_solids(t_rt *rt);
void	print_cam_base(t_rt *rt);

void	free_rt(t_rt *rt);
int		exit_minirt(t_rt *rt);

int		key_hook(int keycode, t_rt *rt);
void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color);
t_rgb	shaker_ambiant_solid(t_rt *rt, t_rgb color, t_rgb diffuse);
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color);

#endif
