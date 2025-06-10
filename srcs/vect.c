/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:45:57 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/10 17:58:32 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"
#include "math.h"

t_vect	vec_prod(t_vect u, t_vect v)
{
	return ((t_vect)
		{
			u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x,
		});
}

t_vect	vec_add(t_vect u, t_vect v)
{
	return ((t_vect)
		{
			u.x + v.x,
			u.y + v.y,
			u.z + v.z,
		});
}

t_vect	vec_sub(t_vect u, t_vect v)
{
	return ((t_vect)
		{
			u.x - v.x,
			u.y - v.y,
			u.z - v.z,
		});
}

t_vect	vec(double x, double y, double z)
{
	return ((t_vect)
		{
			x,
			y,
			z,
		});
}

t_vect	vec_mul(t_vect u, double k)
{
	return ((t_vect)
		{
			u.x * k,
			u.y * k,
			u.z * k,
		});
}

double	vec_norm(t_vect u)
{
	return (sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2)));
}

t_vect	get_point(t_vect start, t_vect dir, double norm)
{
	double	t;

	t = sqrt(pow(norm, 2) / (pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2)));
	return ((t_vect)
		{
			start.x + dir.x * t,
			start.y + dir.y * t,
			start.z + dir.z * t,
		});
}
