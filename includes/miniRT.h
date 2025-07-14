/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/14 10:31:41 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "miniRT_type.h"
# include "miniRT_inter.h"

# define WIN_X	710
# define WIN_Y	710

void	check_args(int argc);
int		print_error(char *message, char *complement);

int		fill_vec(char *str, t_vect *vec);
int		fill_rgb(char *str, t_rgb *color, char *error);

int		get_cam_info(char **tok, t_rt *rt);
int		get_light_info(char **tok, t_rt *rt);
int		get_ambient_info(char **tok, t_rt *rt);
int		get_sphere_info(char **tok, t_rt *rt);
int		get_cylinder_info(char **tok, t_rt *rt);
int		get_plane_info(char **tok, t_rt *rt);
int		get_cone_info(char **tok, t_rt *rt);

void	set_co(t_co *co);
void	set_cy(t_cy *cy);
void	set_pl(t_pl *pl);
void	set_sp(t_sp *sp);
void	set_cam_base(t_cam *cam);
void	set_base(t_base *base, t_vect direction_n);

void	print_solids(t_rt *rt);
void	print_cam_base(t_rt *rt);

void	free_rt(t_rt *rt);
int		exit_minirt(t_rt *rt);

int		key_hook(int keycode, t_rt *rt);
int		select_solid(int button, int x, int y, t_rt *rt);

void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color);
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color);
void	put_string(t_rt *rt);

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular);
t_rgb	color_mul(t_rgb	c1, t_rgb c2);
t_rgb	color_add(t_rgb	c1, t_rgb c2);
t_rgb	color_k(t_rgb	c1, float k);

t_vect	normal_vect(t_inter inter, t_vect point);
t_vect	ray_from_camera_to_objects(t_cam cam, double x, double y);

t_rgb	get_sp_checkerboard(t_vect point, t_sp *sp);
t_rgb	get_pl_checkerboard(t_vect point, t_pl *pl);
t_rgb	get_cy_checkerboard(t_vect point, t_cy *cy);
t_rgb	get_cyd_checkerboard(t_vect point, t_cy *cy, t_type mode);

#endif
