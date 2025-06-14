/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/14 21:41:37 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "math_utils.h"
# include "assert.h"

# define WIN_X	1920
# define WIN_Y	1080

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

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE
}	t_type;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_cam
{
	t_vect	position;
	t_vect	direction;
	float	fov;
}	t_cam;

typedef struct s_ambient
{
	float	lighting;
	t_rgb	color;
}	t_ambient;

typedef struct light
{
	t_vect	position;
	float	brightness;
	// t_rgb	color;
}	t_light;

typedef struct s_sp
{
	t_type	type;
	t_vect	center;
	float	diameter;
	t_rgb	color;
}	t_sp;

typedef struct s_pl
{
	t_type	type;
	t_vect	point;
	t_vect	normal;
	double	d;
	t_rgb	color;
}	t_pl;

typedef struct s_cy
{
	t_type	type;
	t_vect	center;
	t_vect	axis;
	float	diameter;
	float	height;
	t_vect	top;
	t_vect	bottom;
	double	dt;
	double	db;
	t_rgb	color;
}	t_cy;

typedef struct s_cam_base
{
	t_vect	h_dir;
	t_vect	v_dir;
	t_vect	start;
	t_vect	pixel_x;
	t_vect	pixel_y;
}	t_cam_base;

typedef struct s_inter
{
	t_vect	point;
	t_rgb	color;
	int		init;
}	t_inter;

typedef struct s_menu
{
	int	obj;
	int	value;
}	t_menu;

typedef struct s_rt
{
	t_mlx		mlx;
	t_cam		camera;
	t_cam_base	c_base;
	t_light		light;
	t_ambient	ambiant;
	int			nb_object;
	t_type		*object[20];
	t_type		*cam_obj[20];
	t_menu		menu;
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

void	set_cam_base(t_rt *rt);//
void	set_cam_obj(t_rt *rt);

void	throwing_rays_through_the_wide_universe(t_rt *rt);

void	inter_sphere(t_rt *rt, t_vect ray, t_inter *inter, t_sp *sp);
void	inter_cylinder(t_rt *rt, t_vect ray, t_inter *inter, t_cy*cy);
void	inter_plane(t_rt *rt, t_vect ray, t_inter *inter, t_pl *pl);

void	print_solids(t_rt *rt);
void	print_cam_base(t_rt *rt);

void	free_rt(t_rt *rt);
int		exit_minirt(t_rt *rt);

int		key_hook(int keycode, t_rt *rt);
void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color);

#endif
