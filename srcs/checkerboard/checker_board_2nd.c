/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board_2nd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 09:25:29 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <assert.h>

#define CHECK_R 255
#define CHECK_G 0
#define CHECK_B 255
#define CHECK_COLOR 0xFF0000

static void	linear_remap(double *to_remap, double min, double max)
{
	*to_remap = min + (max - min) * *to_remap;
}

void	get_cy_map(t_vect point, t_cy *cy, t_vect *map)
{
	t_vect		p;

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
}

void	get_cy_disk_map(t_vect point, t_cy *cy, t_type mode, t_vect *map)
{
	t_vect	p;

	if (mode == DISK_BOT)
		p = vec_sub(point, cy->bottom);
	else
		p = vec_sub(point, cy->top);
	map->x = atan2(dot(p, cy->base.h_normal), dot(p, cy->base.v_normal));
	map->x /= 2 * PI;
	map->x += 0.5;
	if (map->x < 0)
		map->x += 1.0;
	if (map->x > 1)
		map->x -= 1.0;
	map->y = (norm(p) / cy->radius);
	if (mode == DISK_BOT)
		linear_remap(&map->y, 0, 0.2);
	else
		linear_remap(&map->y, 0.8, 1);
}

void	get_co_map(t_vect point, t_co *co, t_vect *map)
{
	t_vect		p;

	p = vec_sub(co->center, point);
	map->x = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	map->x /= 2 * PI;
	while (map->x < 0)
		map->x += 1.0;
	while (map->x > 1)
		map->x -= 1.0;
	map->y = dot(co->axis_n, p);
	map->y /= co->height;
	map->y *= -1;
	while (map->y < 0)
		map->y += 1.0;
	while (map->y > 1)
		map->y -= 1.0;
	linear_remap(&map->y, 0, 0.8);
}

void	get_co_disk_map(t_vect point, t_co *co, t_vect *map)
{
	t_vect	p;

	p = vec_sub(point, co->center);
	map->x = atan2(dot(p, co->base.h_normal), dot(p, co->base.v_normal));
	map->x /= 2 * PI;
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
}
