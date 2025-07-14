/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/14 17:21:49 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "stdio.h"

#define CHECK_R 255
#define CHECK_G 0
#define CHECK_B 255

t_rgb	get_sp_checkerboard(t_vect point, t_sp *sp)
{
	int		theta;
	int		phi;
	t_vect	p;

	p = vec_sub(point, sp->center);
	phi = (int)floor(10 * atan(p.x / p.y) / (PI));
	theta = (int)floor(10 * acos(p.z / sp->radius) / (PI));
	if ((theta + phi) % 2)
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
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
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
	else
		return (pl->color);
}

t_rgb	get_cy_checkerboard(t_vect point, t_cy *cy)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, cy->center);
	theta = (int)floor(6 * atan(dot(p, cy->base.h_normal) / dot(p, cy->base.v_normal)) / (PI));	
	alpha = (int)floor(3 * dot(cy->axis_n, p));
	if ((theta + alpha) % 2)
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
	else
		return (cy->color);
}

t_rgb	get_co_checkerboard(t_vect point, t_co *co)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, co->center);
	theta = (int)floor(6 * atan(dot(p, co->base.h_normal) / dot(p, co->base.v_normal)) / (PI));	
	alpha = (int)floor(3 * dot(co->axis_n, p));
	if ((theta + alpha) % 2)
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
	else
		return (co->color);
}

t_rgb	get_cyd_checkerboard(t_vect point, t_cy *cy, t_type mode)
{
	int		theta;
	int		alpha;
	t_vect	p;

	if (mode == DISK_BOT)
		p = vec_sub(point, cy->bottom);
	else
		p = vec_sub(point, cy->top);
	theta = (int)floor(6 * atan(dot(p, cy->base.h_normal) / dot(p, cy->base.v_normal)) / (PI));
	alpha = (int)floor(2 * (norm(p) / cy->radius));
	if ((((theta + alpha) % 2) && mode == DISK_BOT) || (!((theta + alpha) % 2) && mode == DISK_TOP))
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
	else
		return (cy->color);
}

t_rgb	get_cod_checkerboard(t_vect point, t_co *co)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, co->center);
	theta = (int)floor(6 * atan(dot(p, co->base.h_normal) / dot(p, co->base.v_normal)) / (PI));
	alpha = (int)floor(2 * (norm(p) / co->radius));
	if (!((theta + alpha) % 2))
		return ((t_rgb){CHECK_R, CHECK_G, CHECK_B});
	else
		return (co->color);
}

t_rgb	get_disk_checkerboard(t_vect point, t_type *obj, t_type mode)
{
	if (mode == DISK)
		return (get_cod_checkerboard(point, (t_co *)obj));
	else
		return (get_cyd_checkerboard(point, (t_cy *)obj, mode));
}
