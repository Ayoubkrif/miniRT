/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/12 15:09:58 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "stdio.h"

t_rgb	get_sp_checkerboard(t_vect point, t_sp *sp)
{
	int		theta;
	int		phi;
	t_vect	p;

	p = vec_sub(point, sp->center);
	phi = (int)floor(10 * atan(p.x / p.y) / (PI));
	theta = (int)floor(10 * acos(p.z / sp->radius) / (PI));
	if ((theta + phi) % 2)
		return ((t_rgb){0, 0, 0});
	else
		return (sp->color);
}

t_rgb	get_pl_checkerboard(t_vect point, t_pl *pl)
{
	t_vect	p;
	int		alpha;
	int		beta;

	p = vec_sub(point, pl->point);
	alpha = (int)floor(dot(pl->base.h_normal, p));
	beta = (int)floor(dot(pl->base.v_normal, p));
	if (((alpha + beta)) % 2)
		return ((t_rgb){0, 0, 0});
	else
		return (pl->color);
}

t_rgb	get_cy_checkerboard(t_vect point, t_cy *cy)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, cy->center);
	theta = (int)floor(5 * atan(p.x / p.y) / (PI));
	alpha = (int)floor(1.5 * dot(cy->axis_n, p));
	if ((theta + alpha) % 2)
		return ((t_rgb){0, 0, 0});
	else
		return (cy->color);
}
