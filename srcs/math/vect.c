/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:45:57 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/02 14:37:48 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

t_vect	cross(t_vect u, t_vect v)
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
