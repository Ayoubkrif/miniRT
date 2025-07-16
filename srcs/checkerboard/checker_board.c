/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/16 19:26:32 by aykrifa          ###   ########.fr       */
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

void	get_obj_map(t_vect *point, t_type *obj, t_vect *map, t_type mode)
{
	if (mode == SPHERE)
		get_sp_map(*point, (t_sp *)obj, map);
	if (mode == PLANE)
		get_pl_map(*point, (t_pl *)obj, map);
	if (mode == CYLINDER)
		get_cy_map(*point, (t_cy *)obj, map);
	if (mode >= DISK)
		get_disk_map(*point, obj, mode, map);
	if (mode == CONE)
		get_co_map(*point, (t_co *)obj, map);
}

void	get_solid_color_normal(t_inter *inter, t_vect *normal, int *color, t_vect *point)
{
	t_vect	map;
	t_obj	*obj = (t_obj *)inter->obj;

	*normal = normal_vect(*inter, *point);
	if (inter->map)
	{
		get_obj_map(point, inter->obj, &map, inter->mode);
	}
	if (!(inter->map % 3))
		*color = inter->color;
	else if (inter->map % 3 == 1)
	{
		if ((int)(floor(10 * map.x) + floor(10 * map.y)) % 2)
			*color = CHECK_COLOR;
		else
			*color = inter->color;
	}
	else
		*color = my_mlx_pixel_get(obj->texture.img, map.x * obj->texture.width, (map.y) * obj->texture.height);
}

void	get_sp_map(t_vect point, t_sp *sp, t_vect *map)
{
	t_vect		p;

	p = vec_sub(point, sp->center);
	map->x = atan2(p.y, p.x);
	if (map->x < 0)
		map->x += 2.0 * PI;
	map->y = acos(p.z / sp->radius);
	map->x /= (2.0 * PI);
	map->y /= PI;
	/*if (sp->map == 1)*/
	/*	return (my_mlx_pixel_get(img, phi * img->width, (theta) * img->height));*/
	/*if ((int)(floor(10 * theta) + floor(10 * phi)) % 2)*/
	/*	return (CHECK_COLOR);*/
	/*else*/
	/*	return (sp->color);*/
}

void	get_pl_map(t_vect point, t_pl *pl, t_vect *map)
{
	t_vect	p;

	p = vec_sub(point, pl->point);
	map->x = floor(dot(pl->base.h_normal, p));
	map->y = floor(dot(pl->base.v_normal, p));
	/*t_img	*img;*/
	/*img = pl->texture.img;*/
	/*if (pl->map == 1)*/
	/*	return (my_mlx_pixel_get(img, map->x * img->width, (map->y) * img->height));*/
	/*if (((int)(map->x + map->y)) % 2)*/
	/*	return (CHECK_COLOR);*/
	/*else*/
	/*	return (pl->color);*/
}
