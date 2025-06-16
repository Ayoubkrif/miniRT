/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 13:33:41 by aykrifa          ###   ########.fr       */
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
	return ((t_vect)
		{
			start.x + dir.x * t,
			start.y + dir.y * t,
			start.z + dir.z * t,
		});
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
