/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 19:17:23 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"
#include "math.h"
#include <assert.h>

double	vec_norm(t_vect u)
{
	return (sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2)));
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

	assert(!(dir.x == 0 && dir.y == 0 && dir.z == 0));
	t = sqrt(pow(norm, 2) / (pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2)));
	return (get_point_d(start, dir, t));
}

double	dot_prod(t_vect u, t_vect v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}
