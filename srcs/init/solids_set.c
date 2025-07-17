/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solids_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:30:54 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 09:31:00 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cy(t_cy *cy)
{
	set_base(&cy->base, cy->axis_n);
	cy->semi_height = cy->height / 2;
	cy->radius = cy->diameter / 2;
	cy->top = get_point_t(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot(cy->top, cy->axis_n);
	cy->bottom = get_point_t(cy->center, vec_mul(cy->axis_n, -1),
			cy->semi_height);
	cy->db = -dot(cy->bottom, cy->axis_n);
}

void	set_sp(t_sp *sp)
{
	sp->radius = sp->diameter / 2;
}

void	set_pl(t_pl *pl)
{
	pl->d = -dot(pl->point, pl->normal_n);
	set_base(&pl->base, pl->normal_n);
}

void	set_co(t_co *co)
{
	set_base(&co->base, co->axis_n);
	co->radius = co->diameter / 2;
	co->gamma = p2(co->height) / (p2(co->radius) + p2(co->height));
	co->theta = atan(co->radius / co->height);
	co->center = get_point_t(co->apex, co->axis_n, co->height);
	co->d = -dot(co->center, co->axis_n);
}
