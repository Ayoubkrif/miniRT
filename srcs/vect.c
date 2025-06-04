/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:45:57 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/04 19:12:59 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){
		.x = u.y * v.z - u.z * v.y,
		.y = u.z * v.x - u.x * v.z,
		.z = u.x * v.y - u.y * v.x,
	});
}

t_vec3	vect_add(t_vec3 u, t_vec3 v)
{
	return ((t_vec3){
		.x = u.x + v.x,
		.y = u.y + v.y,
		.z = u.z + v.z,
	});
}
