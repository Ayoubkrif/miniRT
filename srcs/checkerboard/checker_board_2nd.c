/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board_2nd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/16 17:39:46 by aykrifa          ###   ########.fr       */
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

void	linear_remap(double *to_remap, double min, double max)
{
	*to_remap = min + (max - min) * *to_remap;
}

void	get_cy_map(t_vect point, t_cy *cy, t_vect *map)
{
	t_vect		p;
	t_img		*img;

	img = cy->texture.img;
	p = vec_sub(point, cy->center);
	map->x = atan2(dot(p, cy->base.h_normal), dot(p, cy->base.v_normal));
	map->x /= 2 * PI;
	map->x += 0.5;
	if (map->x < 0)
		map->x += 1.0;
	if (map->x > 1)
		map->x -= 1.0;
	map->y = dot(cy->axis_n, p);
	map->y /= cy->height;
	map->y += 0.5;
	linear_remap(&map->y, 0.2, 0.8);
	if (cy->map == 1)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if ((int)(floor(10 * theta) + floor(10 * alpha)) % 2)
		return (CHECK_COLOR);
	else
		return (cy->color);
}

void	get_cyd_map(t_vect point, t_cy *cy, t_type mode)
{
	float	theta;
	float	alpha;
	t_vect	p;
	t_img		*img;

	img = cy->texture.img;
	if (mode == DISK_BOT)
		p = vec_sub(point, cy->bottom);
	else
		p = vec_sub(point, cy->top);
	theta = atan2(dot(p, cy->base.h_normal), dot(p, cy->base.v_normal));
	theta /= 2 * PI;
	theta += 0.5;
	if (theta < 0)
		theta += 1.0;
	if (theta > 1)
		theta -= 1.0;
	alpha = (norm(p) / cy->radius);
	if (mode == DISK_BOT)
		linear_remap(&alpha, 0, 0.2);
	else
		linear_remap(&alpha, 0.8, 1);
	if (cy->map == 1)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if ((mode == DISK_BOT && (int)(floor(theta * 10) + floor(alpha * 10)) % 2)
			|| (mode == DISK_TOP && ((int)(floor(10 * theta) + floor(10 * alpha))) % 2 == 0))
		return (CHECK_COLOR);
	else
		return (cy->color);
}

void	get_co_map(t_vect point, t_co *co)
{
	float		theta;
	float		alpha;
	t_vect		p;
	t_img		*img;

	img = co->texture.img;
	p = vec_sub(co->center, point);
	theta = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	theta /= 2 * PI;
	/*theta *= -1;*/
	while (theta < 0)
		theta += 1.0;
	while (theta > 1)
		theta -= 1.0;
	alpha = dot(co->axis_n, p);
	alpha /= co->height;
	alpha *= -1;
	while (alpha < 0)
		alpha += 1.0;
	while (alpha > 1)
		alpha -= 1.0;
	linear_remap(&alpha, 0, 0.8);
	if (co->map == 1)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if ((int)(floor(10 * theta) + floor(10 * alpha)) % 2)
		return (CHECK_COLOR);
	else
		return (co->color);
}

void	get_co_disk_map(t_vect point, t_co *co, t_vect *map)
{
	t_vect	p;
	t_img	*img;

	img = co->texture.img;
	p = vec_sub(point, co->center);
	map->x = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	map->x /= 2 * PI;
	/*map->x *= -1;*/
	map->x += 0.5;
	while (map->x < 0)
		map->x += 1.0;
	while (map->x > 1)
		map->x -= 1.0;
	map->y = norm(p) / co->radius;
	map->y *= -1;
	while (map->y < 0)
		map->y += 1.0;
	while (map->y > 1)
		map->y -= 1.0;
	linear_remap(&map->y, 0.8, 1);
	if (co->map == 1)
		return (my_mlx_pixel_get(img, theta * img->width, (alpha) * img->height));
	if (((int)(floor(10 * theta) + floor(10 * alpha))) % 2)
		return (CHECK_COLOR);
	else
		return (co->color);
}

void	get_disk_map(t_vect point, t_type *obj, t_type mode)
{
	if (mode == DISK)
		return (get_co_disk_map(point, (t_co *)obj));
	else
		return (get_cy_disk_map(point, (t_cy *)obj, mode));
}
