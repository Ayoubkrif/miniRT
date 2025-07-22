/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 13:40:34 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

#define CHECK_R 255
#define CHECK_G 0
#define CHECK_B 255
#define CHECK_COLOR 0xF000FF

void	get_obj_map(t_vect *point, t_obj *obj, t_vect *map, t_type mode)
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
	map->y += obj->v_offset;
	while (map->y < 0)
		map->y += 1.0;
	while (map->y > 1)
		map->y -= 1.0;
	map->x += obj->u_offset;
	while (map->x < 0)
		map->x += 1.0;
	while (map->x > 1)
		map->x -= 1.0;
}

void	checkerboard(t_inter *inter, int *color, t_vect *map)
{
	if ((int)(floor(10 * map->x) + floor(10 * map->y)) % 2)
		*color = CHECK_COLOR;
	else
		*color = inter->obj->color;
}

void	bump_texture(
		t_inter *inter, t_vect *normal, int *color, t_vect *point)
{
	t_vect	map;
	t_obj	*obj;
	int		temp;

	obj = (t_obj *)inter->obj;
	*normal = normal_vect(*inter, *point);
	if (!inter->obj->map)
	{
		*color = inter->obj->color;
		return ;
	}
	get_obj_map(point, inter->obj, &map, inter->mode);
	temp = inter->obj->map & 0b11;
	if (temp == 1)
		checkerboard(inter, color, &map);
	else if (temp == 2)
		*color = my_mlx_pixel_get(obj->texture.img,
				map.x * obj->texture.width, map.y * obj->texture.height);
	else
		*color = inter->obj->color;
	if (inter->obj->map >= 4)
		bump_normal(&obj->bump, normal, &map, 10);
}
