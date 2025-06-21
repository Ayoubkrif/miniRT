/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/21 15:09:05 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

void	push_inter(t_type *obj, t_rgb color, double t, t_inter *inter, t_type mode)
{
	if (t > 0 && (!inter->obj || inter->t > t))
		*inter = (t_inter){t, color, obj, mode};
}

void	inter_sphere(t_vect ray, t_sp *sp, t_inter *inter, t_vect start)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = dot_prod(ray, ray);
	b = 2 * dot_prod(ray, vec_sub(start, sp->center));
	c = p2(vec_norm(vec_sub(start, sp->center))) - p2(sp->radius);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	push_inter((t_type *)sp, sp->color, (-b + sqrt(delta))
		/ (2 * a), inter, SPHERE);
	push_inter((t_type *)sp, sp->color, (-b - sqrt(delta))
		/ (2 * a), inter, SPHERE);
}

void	inter_disk(t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	dot_axis_start;
	double	t;

	dot_n_ray = dot_prod(ray, cy->axis_n);
	if (!dot_n_ray)
		return ;
	dot_axis_start = dot_prod(cy->axis_n, start);
	t = - (dot_axis_start + cy->dt) / dot_n_ray;
	if (vec_norm(vec_sub(cy->top, get_point_d(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter, DISK_TOP);
	t = - (dot_axis_start + cy->db) / dot_n_ray;
	if (vec_norm(vec_sub(cy->bottom, get_point_d(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter, DISK_BOT);
}

void	inter_cylinder(t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vect	d_cam_center;
	t_vect	prod_d_cy;
	t_vect	prod_ray_cy;

	d_cam_center = vec_sub(cy->center, start);
	prod_ray_cy = vec_prod(cy->axis_n, ray);
	prod_d_cy = vec_prod(cy->axis_n, d_cam_center);
	a = dot_prod(prod_ray_cy, prod_ray_cy);
	if (!double_eq(a, 0)) // a != 0 
	{
		b = -2 * dot_prod(prod_d_cy, prod_ray_cy);
		c = dot_prod(prod_d_cy, prod_d_cy) - p2(cy->radius);
		delta = delta_2nd(a, b, c);
		double	root;
		if (delta > 0)
		{
			delta = sqrt(delta);
			root = dot_prod(cy->axis_n, vec_sub(get_point_d(start, ray, (-b + delta) / (2 * a)), cy->center));
			if (fabs(root) <= cy->semi_height)
				push_inter((t_type *)cy, cy->color, (-b + delta) / (2 * a), inter, CYLINDER);
			root = dot_prod(cy->axis_n, vec_sub(get_point_d(start, ray, (-b - delta) / (2 * a)), cy->center));
			if (fabs(root) <= cy->semi_height)
				push_inter((t_type *)cy, cy->color, (-b - delta) / (2 * a), inter, CYLINDER);
		}
	}
	inter_disk(ray, cy, inter, start);
}

void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	t;

	dot_n_ray = dot_prod(ray, pl->normal_n);
	if (!dot_n_ray)
		return ;
	t = - (dot_prod(pl->normal_n, start) + pl->d) / dot_n_ray;
	push_inter((t_type *)pl, pl->color, t, inter, PLANE);
}
