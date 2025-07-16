/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/16 13:09:24 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "stdio.h"
#include	"mlx_int.h"
#include <assert.h>

#define CHECK_R 255
#define CHECK_G 0
#define CHECK_B 255
#define CHECK_COLOR 0xF000FF

int	get_sp_checkerboard(t_vect point, t_sp *sp)
{
	float		theta;
	float		phi;
	t_vect		p;
	t_img		*img;

	img = sp->texture.img;
	p = vec_sub(point, sp->center);
	phi = atan2(p.y, p.x);
	if (phi < 0)
		phi += 2.0 * PI;
	theta = acos(p.z / sp->radius);
	phi /= (2.0 * PI);
	theta /= PI;
	if (sp->map == 1)
		return (my_mlx_pixel_get(img, phi * img->width, (theta) * img->height));
	if ((int)(floor(10 * theta) + floor(10 * phi)) % 2)
		return (CHECK_COLOR);
	else
		return (sp->color);
}

int	get_pl_checkerboard(t_vect point, t_pl *pl)
{
	t_vect	p;
	float	alpha;
	float	beta;
	t_img	*img;

	img = pl->texture.img;
	p = vec_sub(point, pl->point);
	alpha = floor(dot(pl->base.h_normal, p));
	beta = floor(dot(pl->base.v_normal, p));
	if (pl->map == 1)
		return (my_mlx_pixel_get(img, alpha * img->width, (beta) * img->height));
	if (((int)(alpha + beta)) % 2)
		return (CHECK_COLOR);
	else
		return (pl->color);
}
