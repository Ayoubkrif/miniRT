/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/05 13:28:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

void	push_inter(t_type *obj, t_rgb color, double t, t_inter *inter, t_type mode)
{
	if (t > EPSILON && (!inter->obj || inter->t > t))
		*inter = (t_inter){t, color, obj, mode};
}

void	inter_sphere(t_vect ray, t_sp *sp, t_inter *inter, t_vect start)
{
	t_quadratic	quad;

	quad.a = dot(ray, ray);
	if (double_eq(quad.a, 0))
		return ;
	quad.b = 2 * dot(ray, vec_sub(start, sp->center));
	quad.c = p2(norm(vec_sub(start, sp->center))) - p2(sp->radius);
	if (!delta_2nd(&quad))
		return ;
	push_inter((t_type *)sp, sp->color, quad.root, inter, SPHERE);
}

void	inter_disk(t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	dot_axis_start;
	double	t;

	dot_n_ray = dot(ray, cy->axis_n);
	if (!dot_n_ray)
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

void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	t;

	dot_n_ray = dot(ray, pl->normal_n);
	if (!dot_n_ray)
		return ;
	t = - (dot(pl->normal_n, start) + pl->d) / dot_n_ray;
	push_inter((t_type *)pl, pl->color, t, inter, PLANE);
}
