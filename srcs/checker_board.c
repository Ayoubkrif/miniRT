/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/15 13:57:48 by cbordeau         ###   ########.fr       */
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

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	// printf("x is %d, y is %d\n", x, y);
	dst = img->data + (y * img->size_line
			+ x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_sp_checkerboard(t_vect point, t_sp *sp)
{
	float		theta;
	float		phi;
	t_vect		p;
	t_img		*img;

	img = sp->texture.img;
	p = vec_sub(point, sp->center);
	phi = (atan(p.x / p.y) / (PI)) + 0.5;
	theta = acos(p.z / sp->radius) / (PI);
	if (phi < 0)
	{
		printf("theta is %f, phi is %f\n", theta, phi);
		phi = 0;
	}
	if (phi > 1)
	{
		printf("theta is %f, phi is %f\n", theta, phi);
		phi = 1;
	}
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
	int		alpha;
	int		beta;

	p = vec_sub(point, pl->point);
	alpha = (int)floor(dot(pl->base.h_normal, p));
	beta = (int)floor(dot(pl->base.v_normal, p));
	if (((alpha + beta)) % 2)
		return (CHECK_COLOR);
	else
		return (pl->color);
}
		// return (*(img->data + (int)((theta / 10) * img->width + (phi / 10) * img->height * img->bpp / 8)));

int	get_cy_checkerboard(t_vect point, t_cy *cy)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, cy->center);
	theta = (int)floor(6 * atan(dot(p, cy->base.h_normal) / dot(p, cy->base.v_normal)) / (PI));	
	alpha = (int)floor(3 * dot(cy->axis_n, p));
	if ((theta + alpha) % 2)
		return (CHECK_COLOR);
	else
		return (cy->color);
}

int	get_co_checkerboard(t_vect point, t_co *co)
{
	int		theta;
	int		alpha;
	t_vect	p;

	p = vec_sub(point, co->center);
	theta = (int)floor(6 * atan(dot(p, co->base.h_normal) / dot(p, co->base.v_normal)) / (PI));	
	alpha = (int)floor(3 * dot(co->axis_n, p));
	if ((theta + alpha) % 2)
		return (CHECK_COLOR);
	else
		return (co->color);
}

int	get_cyd_checkerboard(t_vect point, t_cy *cy, t_type mode)
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
	theta = (int)floor(6 * atan(dot(p, co->base.h_normal) / dot(p, co->base.v_normal)) / (PI));
	alpha = (int)floor(2 * (norm(p) / co->radius));
	if (!((theta + alpha) % 2))
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
