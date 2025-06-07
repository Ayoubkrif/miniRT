/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:45:57 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/07 14:38:27 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	return ((t_vec3)
		{
			u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x,
		});
}

t_vec3	vect_add(t_vec3 u, t_vec3 v)
{
	return ((t_vec3)
		{
			u.x + v.x,
			u.y + v.y,
			u.z + v.z,
		});
}
