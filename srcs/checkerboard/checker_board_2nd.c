/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board_2nd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/16 12:18:04 by aykrifa          ###   ########.fr       */
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

int	my_mlx_pixel_get(t_img *img, int x, int y);

void	linear_remap(float *to_remap, float min, float max)
{
	*to_remap = min + (max - min) * *to_remap;
}

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

int	get_cy_checkerboard(t_vect point, t_cy *cy)
{
	float		theta;
	float		alpha;
	t_vect		p;
	t_img		*img;

	img = cy->texture.img;
	p = vec_sub(point, cy->center);
	theta = atan2(dot(p, cy->base.h_normal), dot(p, cy->base.v_normal));
	theta /= 2 * PI;
	if (theta < 0)
		theta += 1.0;
	alpha = dot(cy->axis_n, p);
	alpha /= cy->height;
	alpha += 0.5;
	linear_remap(&alpha, 0.2, 0.8);
	if (cy->map == 1)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if ((int)(floor(10 * theta) + floor(10 * alpha)) % 2)
		return (CHECK_COLOR);
	else
		return (cy->color);
}

int	get_co_checkerboard(t_vect point, t_co *co)
{
	float		theta;
	float		alpha;
	t_vect		p;
	t_img		*img;

	img = co->texture.img;
	p = vec_sub(point, co->center);
	theta = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	theta /= 2 * PI;
	if (theta < 0)
		theta += 1.0;
	alpha = dot(co->axis_n, p);
	alpha /= co->height;
	alpha += 0.5;
	linear_remap(&alpha, 0.2, 0.8);
	if (co->map == 5)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if ((int)(floor(10 * theta) + floor(10 * alpha)) % 2)
		return (CHECK_COLOR);
	else
		return (co->color);
}

int	get_cyd_checkerboard(t_vect point, t_cy *cy, t_type mode)
{
	float	theta;
	float	alpha;
	t_vect	p;

	if (mode == DISK_BOT)
		p = vec_sub(point, cy->bottom);
	else
		p = vec_sub(point, cy->top);
	theta = atan2(dot(p, cy->base.h_normal), dot(p, cy->base.v_normal));
	theta /= 2 * PI;
	if (theta < 0)
		theta += 1.0;
	alpha = (norm(p) / cy->radius);
	if (mode == DISK_BOT)
		linear_remap(&alpha, 0, 0.2);
	else
		linear_remap(&alpha, 0.8, 1);
	if ((mode == DISK_BOT && (int)(floor(theta * 5) + floor(alpha * 5)) % 2)
			|| (mode == DISK_TOP && ((int)(floor(5 * theta) + floor(5 * alpha))) % 2))
		return (CHECK_COLOR);
	else
		return (cy->color);
}

int	get_cod_checkerboard(t_vect point, t_co *co)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, co->center);
	theta = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	theta /= 2 * PI;
	if (theta < 0)
		theta += 1.0;
	alpha = norm(p) / co->radius;
	if (((int)(floor(5 * theta) + floor(5 * alpha))) % 2)
		return (CHECK_COLOR);
	else
		return (co->color);
}

int	get_disk_checkerboard(t_vect point, t_type *obj, t_type mode)
{
	if (mode == DISK)
		return (get_cod_checkerboard(point, (t_co *)obj));
	else
		return (get_cyd_checkerboard(point, (t_cy *)obj, mode));
}
