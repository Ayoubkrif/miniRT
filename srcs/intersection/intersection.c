/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 10:11:11 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_inter.h"
#include <assert.h>
#include "math_utils.h"

void	push_inter(t_obj *obj, double t, t_inter *inter, t_type mode)
{
	if (t > EPSILON && (!inter->obj || inter->t > t))
	{
		*inter = (t_inter){obj, t, mode};
	}
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
	push_inter((t_obj *)sp, quad.root, inter, SPHERE);
}

void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	t;

	dot_n_ray = dot(ray, pl->normal_n);
	if (double_eq(dot_n_ray, 0))
		return ;
	t = - (dot(pl->normal_n, start) + pl->d) / dot_n_ray;
	push_inter((t_obj *)pl, t, inter, PLANE);
}
