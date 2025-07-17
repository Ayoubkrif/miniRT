/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 08:47:13 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "vect.h"
#include <math.h>
#include <stdio.h>

void	push_inter(t_type *obj, int color, double t, t_inter *inter, t_type mode)
{
	if (t > EPSILON && (!inter->obj || inter->t > t))
	{
		*inter = (t_inter){t, color, obj, mode, ((t_obj *)obj)->reflexion, ((t_obj *)obj)->map};
		// if (mode == SPHERE)
		// {
		// 	inter->reflexion = ((t_sp *)obj)->reflexion;
		// 	inter->map = ((t_sp *)obj)->map;
		// }
		// if (mode == PLANE)
		// {
		// 	inter->reflexion = ((t_pl *)obj)->reflexion;
		// 	inter->map = ((t_pl *)obj)->map;
		// }
		// if (mode == CYLINDER || mode == DISK_BOT || mode == DISK_TOP)
		// {
		// 	inter->reflexion = ((t_cy *)obj)->reflexion;
		// 	inter->map = ((t_cy *)obj)->map;
		// }
		// if (mode == CONE || mode == DISK)
		// {
		// 	inter->reflexion = ((t_co *)obj)->reflexion;
		// 	inter->map = ((t_co *)obj)->map;
		// }
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
	push_inter((t_type *)sp, sp->color, quad.root, inter, SPHERE);
}

void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start)
{
	double	dot_n_ray;
	double	t;

	dot_n_ray = dot(ray, pl->normal_n);
	if (double_eq(dot_n_ray, 0))
		return ;
	t = - (dot(pl->normal_n, start) + pl->d) / dot_n_ray;
	push_inter((t_type *)pl, pl->color, t, inter, PLANE);
}
