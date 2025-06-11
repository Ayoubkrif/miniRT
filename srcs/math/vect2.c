/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 14:50:24 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"
#include "math.h"

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

	t = sqrt(pow(norm, 2) / (pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2)));
	return (get_point_d(start, dir, t));
}
