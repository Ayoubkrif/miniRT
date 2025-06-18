/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/18 14:09:59 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"
#include "math_utils.h"

double	vec_norm(t_vect u)
{
	return (sqrt(p2(u.x) + p2(u.y) + p2(u.z)));
}

t_vect	get_point_d(t_vect start, t_vect dir, double t)
{
	return (vec_add(start, vec_mul(dir, t)));
}

t_vect	get_point(t_vect start, t_vect dir, double norm)
{
	double	t;

	/*assert(!(dir.x == 0 && dir.y == 0 && dir.z == 0));*/
	t = sqrt(p2(norm) / (p2(dir.x) + p2(dir.y) + p2(dir.z)));
	return (get_point_d(start, dir, t));
}

double	dot_prod(t_vect u, t_vect v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vect	get_normalized_vec(t_vect u)
{
	return (vec_mul(u, 1 / vec_norm(u)));
}

int	vect_eq(t_vect u, t_vect v)
{
	return (double_eq(u.x, v.x) && double_eq(u.y, v.y) && double_eq(u.z, v.z));
}

int	vect_col(t_vect u, t_vect v)
{
	double	x_div;
	double	y_div;
	double	z_div;

	x_div = u.x / v.x;
	y_div = u.y / v.y;
	z_div = u.z / v.z;
	return (double_eq(x_div, y_div) && double_eq(x_div, z_div));
}
