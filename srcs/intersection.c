/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/18 16:09:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

void	push_inter(t_type *obj, t_rgb color, double t, t_inter *inter)
{
	if (t > 0 && (!inter->obj || inter->t > t))
		*inter = (t_inter){t, color, obj};
}

void	inter_sphere(t_rt *rt, t_vect ray, t_sp *sp, t_inter *inter, t_vect start)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	(void)rt;
	a = dot_prod(ray, ray);
	b = 2 * dot_prod(ray, vec_sub(start, sp->center));
	c = p2(vec_norm(vec_sub(start, sp->center))) - p2(sp->radius);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	push_inter((t_type *)sp, sp->color, (-b + sqrt(delta)) / (2 * a), inter);
	push_inter((t_type *)sp, sp->color, (-b - sqrt(delta)) / (2 * a), inter);
}

void	inter_disk(t_rt *rt, t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	dot_axis_start;
	double	t;
	(void)rt;

	dot_n_ray = dot_prod(ray, cy->axis_n);
	if (!dot_n_ray)
		return ;
	dot_axis_start = dot_prod(cy->axis_n, start);
	t = - (dot_axis_start + cy->dt) / dot_n_ray;
	if (vec_norm(vec_sub(cy->top, get_point_d(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter);
	t = - (dot_axis_start + cy->db) / dot_n_ray;
	if (vec_norm(vec_sub(cy->bottom, get_point_d(start, ray, t))) < cy->radius)
		push_inter((t_type *)cy, cy->color, t, inter);
}

void	inter_cylinder(t_rt *rt, t_vect ray, t_cy *cy, t_inter *inter, t_vect start)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vect	camera;
	t_vect	ortho_ray;
	t_vect	ortho_cam_center;
	t_vect	ray_n;

	ray_n = vec_mul(ray, 1 / vec_norm(ray));
	camera = rt->camera.position;
	ortho_ray = vec_sub(ray_n, vec_mul(cy->axis_n, dot_prod(ray_n, cy->axis_n)));
	ortho_cam_center = vec_sub(camera, cy->center);
	ortho_cam_center = vec_sub(ortho_cam_center, vec_mul(cy->axis_n, dot_prod(ortho_cam_center, cy->axis_n)));

	a = dot_prod(ortho_ray, ortho_ray);
	if (!a)
		return ;
	b = 2 * dot_prod(ortho_cam_center, ortho_ray);
	c = dot_prod(ortho_cam_center, ortho_cam_center) - p2(cy->diameter / 2);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	double	root;

	root = dot_prod(cy->axis_n, vec_sub(cy->center, get_point_d(camera, ray, (-b + sqrt(delta)) / (2 * a))));
	if (root <= cy->semi_height && root >= -cy->semi_height)
		push_inter(rt, cy->color, (-b + sqrt(delta)) / (2 * a));
	root = dot_prod(cy->axis_n, vec_sub(cy->center, get_point_d(camera, ray, (-b - sqrt(delta)) / (2 * a))));
	if (root <= cy->semi_height && root >= -cy->semi_height)
		push_inter(rt, cy->color, (-b - sqrt(delta)) / (2 * a));
	inter_disk(rt, ray, cy, inter, start);
}

void	inter_plane(t_rt *rt, t_vect ray, t_pl *pl, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	t;

	(void)rt;
	dot_n_ray = dot_prod(ray, pl->normal_n);
	if (!dot_n_ray)
		return ;
	t = - (dot_prod(pl->normal_n, start) + pl->d) / dot_n_ray;
	push_inter((t_type *)pl, pl->color, t, inter);
}
