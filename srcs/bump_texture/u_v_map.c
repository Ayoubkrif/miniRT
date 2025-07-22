/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_v_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 11:08:11 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include <math.h>

#define CHECK_R 255
#define CHECK_G 0
#define CHECK_B 255
#define CHECK_COLOR 0xF000FF

void	get_sp_map(t_vect point, t_sp *sp, t_vect *map)
{
	t_vect		p;

	p = vec_sub(point, sp->center);
	map->x = atan2(p.y, p.x);
	map->x /= (2.0 * PI);
	map->y = acos(p.z / sp->radius);
	map->y /= PI;
}

void	get_pl_map(t_vect point, t_pl *pl, t_vect *map)
{
	t_vect	p;

	p = vec_sub(point, pl->point);
	map->x = dot(pl->base.h_normal, p);
	map->y = -dot(pl->base.v_normal, p);
}

void	get_disk_map(t_vect point, t_obj *obj, t_type mode, t_vect *map)
{
	if (mode == DISK)
		return (get_co_disk_map(point, (t_co *)obj, map));
	else
		return (get_cy_disk_map(point, (t_cy *)obj, mode, map));
}
