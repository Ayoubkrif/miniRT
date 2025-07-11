/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/11 17:34:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "math_utils.h"
# include "miniRT_solids.h"
// # include "assert.h"

# define WIN_X	710
# define WIN_Y	710

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
	t_type	mode;
	float	reflexion;
}	t_inter;

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

typedef struct s_rt
{
	t_mlx		mlx;
	t_cam		camera;
	t_light		light[20];
	int			nb_light;
	t_ambient	ambient;
	int			nb_object;
	t_type		*object[20];
	int			menu;
}	t_rt;

void	check_args(int argc);
int		print_error(char *message, char *complement);

int		fill_vec(char *str, t_vect *vec);
int		fill_rgb(char *str, t_rgb *color, char *error);

int		get_cam_info(char **tok, t_rt *rt);
int		get_light_info(char **tok, t_rt *rt);
int		get_ambient_info(char **tok, t_rt *rt);
int		get_sphere_info(char **tok, t_rt *rt);
void	set_sp(t_sp *sp);
int		get_cylinder_info(char **tok, t_rt *rt);
void	set_cy(t_cy *cy);
int		get_plane_info(char **tok, t_rt *rt);
int	get_cone_info(char **tok, t_rt *rt);

void	set_pl(t_pl *pl);
void	set_cam_base(t_cam *cam);
void	set_base(t_base *base, t_vect direction_n);

void	throwing_rays_through_the_wide_universe(t_rt *rt);
t_inter	add_inter(t_rt *rt, t_vect ray, t_vect	start);

void	inter_sphere(t_vect ray, t_sp *sp, t_inter *inter, t_vect start);
void	inter_cylinder(t_vect ray, t_cy*cy, t_inter *inter, t_vect start);
void	inter_disk(t_vect ray, t_cy *cy, t_inter *inter, t_vect start);
void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start);
void	inter_cone(t_vect ray, t_co *co, t_inter *inter, t_vect start);

void	print_solids(t_rt *rt);
void	print_cam_base(t_rt *rt);

void	free_rt(t_rt *rt);
int		exit_minirt(t_rt *rt);

int		key_hook(int keycode, t_rt *rt);
void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color);
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color);
void	put_string(t_rt *rt);

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular, t_light light);
t_rgb	color_mul(t_rgb	c1, t_rgb c2);
t_rgb	color_add(t_rgb	c1, t_rgb c2);
t_rgb	color_k(t_rgb	c1, float k);

t_vect	normal_vect(t_inter inter, t_vect point);
t_vect	ray_from_camera_to_objects(t_cam cam, double x, double y);

t_rgb	get_sp_checkerboard(t_vect point, t_sp *sp);
t_rgb	get_pl_checkerboard(t_vect point, t_pl *pl);
t_rgb	get_cy_checkerboard(t_vect point, t_cy *cy);

#endif
