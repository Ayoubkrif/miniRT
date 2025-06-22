/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/22 13:53:04 by aykrifa          ###   ########.fr       */
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
