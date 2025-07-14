/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/14 10:51:31 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

void	push_inter(t_type *obj, t_rgb color, double t, t_inter *inter, t_type mode);

void	inter_disk(t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	dot_axis_start;
	double	t;

	dot_n_ray = dot(ray, cy->axis_n);
	if (double_eq(dot_n_ray, 0))
		return ;
	dot_axis_start = dot(cy->axis_n, start);
	t = - (dot_axis_start + cy->dt) / dot_n_ray;
	if (norm(vec_sub(cy->top, get_point(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter, DISK_TOP);
	t = - (dot_axis_start + cy->db) / dot_n_ray;
	if (norm(vec_sub(cy->bottom, get_point(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter, DISK_BOT);
}

void	inter_cylinder(t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	t_quadratic	quad;
	t_vect		d_cam_center;
	t_vect		prod_d_cy;
	t_vect		prod_ray_cy;

	d_cam_center = vec_sub(cy->center, start);
	prod_d_cy = cross(cy->axis_n, d_cam_center);
	prod_ray_cy = cross(cy->axis_n, ray);
	quad.a = dot(prod_ray_cy, prod_ray_cy);
	if (double_eq(quad.a, 0))
		return ;
	quad.b = -2 * dot(prod_d_cy, prod_ray_cy);
	quad.c = dot(prod_d_cy, prod_d_cy) - p2(cy->radius);
	if (!delta_2nd(&quad))
		return ;
	if (fabs(dot(cy->axis_n, vec_sub(get_point(start, ray, quad.root), cy->center))) <= cy->semi_height)
		push_inter((t_type *)cy, cy->color, quad.root, inter, CYLINDER);
}

void	inter_cone(t_vect ray, t_co *co, t_inter *inter, t_vect start)
{
	t_quadratic	quad;
	t_vect		delta = vec_sub(start, co->apex);
	double		d_dot_u = dot(co->axis_n, ray);
	double		u_dot_u = dot(ray, ray);
	double		delta_dot_d = dot(delta, co->axis_n);
	double		delta_dot_u = dot(delta, ray);
	double		delta_dot_delta = dot(delta, delta);

	quad.a = (p2(d_dot_u) - co->gamma * u_dot_u);
	if (double_eq(quad.a, 0))
		return ;
	quad.b = 2 * (d_dot_u * delta_dot_d - (co->gamma * delta_dot_u));
	quad.c = p2(delta_dot_d) - (co->gamma * delta_dot_delta);
	if (!delta_2nd(&quad))
		return ;
	double limit = dot(co->axis_n, vec_sub(get_point(start, ray, quad.root), co->center));
	if ( limit <= co->height && limit > 0)
		push_inter((t_type *)co, co->color, quad.root, inter, CONE);
}
