/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 13:31:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include "vect.h"
#include <stdio.h>

void	push_inter(t_rt *rt, t_rgb color, double t)
{
	if (t <= 0)
		return ;
	if (rt->inter.t < 0 || rt->inter.t > t)
		rt->inter = (t_inter){t, color};
}

void	inter_sphere(t_rt *rt, t_vect ray, t_sp *sp)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vect	camera;

	camera = rt->camera.position;
	a = dot_prod(ray, ray);
	b = 2 * dot_prod(ray, vec_sub(camera, sp->center));
	c = p2(vec_norm(vec_sub(camera, sp->center))) - p2(sp->radius);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	push_inter(rt, sp->color, (-b + sqrt(delta)) / (2 * a));
	push_inter(rt, sp->color, (-b - sqrt(delta)) / (2 * a));
}

void	inter_disk(t_rt *rt, t_vect ray, t_cy *cy)
{
	double	dot_n_ray;
	t_vect	camera;
	double	t;

	camera = rt->camera.position;
	dot_n_ray = dot_prod(ray, cy->axis);
	if (!dot_n_ray)
		return ;
	t = - (dot_prod(cy->axis, camera) + cy->dt) / dot_n_ray;
	if (vec_norm(vec_sub(cy->top, get_point_d(camera, ray, t))) < cy->radius)
		push_inter(rt, cy->color, t);
	t = - (dot_prod(cy->axis, camera) + cy->db) / dot_n_ray;
	if (vec_norm(vec_sub(cy->bottom, get_point_d(camera, ray, t))) < cy->radius)
		push_inter(rt, cy->color, t);
}

void	inter_cylinder(t_rt *rt, t_vect ray, t_cy *cy)
{
	inter_disk(rt, ray, cy);
}

void	inter_plane(t_rt *rt, t_vect ray, t_pl *pl)
{
	double	dot_n_ray;
	t_vect	camera;
	double	t;

	camera = rt->camera.position;
	dot_n_ray = dot_prod(ray, pl->normal);
	if (!dot_n_ray)
		return ;
	t = - (dot_prod(pl->normal, camera) + pl->d) / dot_n_ray;
	push_inter(rt, pl->color, t);
}
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*double	delta;*/
	/*t_vect	camera;*/
	/*t_vect	ortho_ray;*/
	/*t_vect	ortho_cam_center;*/
	/*t_vect	axis;*/

	/*axis = vec_mul(cy->axis, 1 / vec_norm(cy->axis));*/
	/*camera = rt->camera.position;*/
	/*ortho_ray = vec_sub(ray, vec_mul(axis, dot_prod(ray, axis)));*/
	/*ortho_cam_center = vec_sub(camera, cy->center);*/
	/*ortho_cam_center = vec_sub(ortho_cam_center, vec_mul(axis, dot_prod(ortho_cam_center, axis)));*/
	/**/
	/*a = dot_prod(ortho_ray, ortho_ray);*/
	/*if (!a)*/
	/*	return ;*/
	/*b = 2 * dot_prod(ortho_cam_center, ortho_ray);*/
	/*c = dot_prod(ortho_cam_center, ortho_cam_center) - p2(cy->diameter / 2);*/
	/*delta = delta_2nd(a, b, c);*/
	/*if (delta <= 0)*/
	/*	return ;*/
	/*double	root;*/
	/**/
	/*root = dot_prod(axis, vec_sub(camera, get_point_d(camera, ray, -b + sqrt(delta) / (2 * a))));*/
	/*if (root <= cy->height / 2 && root >= -cy->height / 2)*/
	/*	push_inter(rt, ray, inter, cy->color, (-b + sqrt(delta)) / (2 * a));*/
	/*root = dot_prod(axis, vec_sub(camera, get_point_d(camera, ray, -b - sqrt(delta) / (2 * a))));*/
	/*if (root <= cy->height / 2 && root >= -cy->height / 2)*/
	/*	push_inter(rt, ray, inter, cy->color, (-b - sqrt(delta)) / (2 * a));*/
