/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/21 16:08:53 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
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

/*float	rgb_to_height(int color, float height)*/
/*{*/
/*	int		r;*/
/*	int		g;*/
/*	int		b;*/
/**/
/*	r = (color >> 16) & 0xFF;*/
/*	g = (color >> 8) & 0xFF;*/
/*	b = color & 0xFF;*/
/*	return (height * (r + g + b) / 765);*/
/*}*/
/**/
/*void	normal_perturbation(t_bump *bump, t_vect *normal, t_vect *map, float height)*/
/*{*/
/*	t_vect	perturbation;*/
/*	t_vect	actu;*/
/*	t_vect	next_h;*/
/*	t_vect	next_v;*/
/*	t_base	new_base;*/
/**/
/*	actu.x = map->x * bump->width;*/
/*	actu.y = map->y * bump->height;*/
/*	actu.z = rgb_to_height(my_mlx_pixel_get(bump->img, actu.x, actu.y), height);*/
/*	next_h.x = actu.x;*/
/*	if (actu.y < bump->height)*/
/*		next_h.y = actu.y + 1;*/
/*	else*/
/*		next_h.y = 0;*/
/*	next_h.z = rgb_to_height(my_mlx_pixel_get(bump->img, next_h.x, next_h.y), height);*/
/*	if (actu.x < bump->width)*/
/*		next_v.x = actu.x + 1;*/
/*	else*/
/*		next_v.x = 0;*/
/*	next_v.y = actu.y;*/
/*	next_v.z = rgb_to_height(my_mlx_pixel_get(bump->img, next_v.x, next_v.y), height);*/
/*	vec_sub_to(&next_v, &actu);*/
/*	vec_sub_to(&next_h, &actu);*/
/*	perturbation = cross(next_h, next_v); //! */
/*	normalize_to(&perturbation);*/
/*	set_base(&new_base, perturbation);*/
/*	vec_mul_to(&new_base.h_normal, perturbation.x);*/
/*	vec_mul_to(&new_base.v_normal, perturbation.y);*/
/*	vec_mul_to(normal, perturbation.z);*/
/*	vec_add_to(normal, &new_base.v_normal);*/
/*	vec_add_to(normal, &new_base.h_normal);*/
/*	normalize_to(normal);*/
/*}*/

float	rgb_to_height(int color, float height)
{
	int	r = (color >> 16) & 0xFF;
	int	g = (color >> 8) & 0xFF;
	int	b = color & 0xFF;
	return (height * (r + g + b) / 765.0f);
}

void	normal_perturbation(t_bump *bump, t_vect *normal, t_vect *map, float height)
{
	int		x = (int)(map->x * (bump->width - 1));
	int		y = (int)(map->y * (bump->height - 1));

	// Sécurisation des bords
	int		xm1 = (x > 0) ? x - 1 : x;
	int		xp1 = (x < bump->width - 1) ? x + 1 : x;
	int		ym1 = (y > 0) ? y - 1 : y;
	int		yp1 = (y < bump->height - 1) ? y + 1 : y;

	// Lecture des hauteurs voisines
	float	hL = rgb_to_height(my_mlx_pixel_get(bump->img, xm1, y), height);
	float	hR = rgb_to_height(my_mlx_pixel_get(bump->img, xp1, y), height);
	float	hD = rgb_to_height(my_mlx_pixel_get(bump->img, x, ym1), height);
	float	hU = rgb_to_height(my_mlx_pixel_get(bump->img, x, yp1), height);

	// Estimation des dérivées
	float	dhx = (hR - hL) * 0.5f;
	float	dhy = (hU - hD) * 0.5f;

	// Normale bump (dans l’espace de la heightmap)
	t_vect bump_normal = {-dhx, -dhy, 1.0f};
	normalize_to(&bump_normal);

	// Transformation vers l’espace local de la surface
	t_base base;
	set_base(&base, *normal); // *normal est la normale originale

	t_vect new_normal;
	new_normal.x = bump_normal.x * base.h_normal.x +
				   bump_normal.y * base.v_normal.x +
				   bump_normal.z * normal->x;
	new_normal.y = bump_normal.x * base.h_normal.y +
				   bump_normal.y * base.v_normal.y +
				   bump_normal.z * normal->y;
	new_normal.z = bump_normal.x * base.h_normal.z +
				   bump_normal.y * base.v_normal.z +
				   bump_normal.z * normal->z;

	normalize_to(&new_normal);
	*normal = new_normal;
}


void	get_color_normal(
		t_inter *inter, t_vect *normal, int *color, t_vect *point)
{
	t_vect	map;
	t_obj	*obj;

	obj = (t_obj *)inter->obj;
	*normal = normal_vect(*inter, *point);
	if (!inter->obj->map)
	{
		*color = inter->obj->color;
		return ;
	}
	get_obj_map(point, inter->obj, &map, inter->mode);
	int		temp;

	temp = inter->obj->map & 0b11;
	if (temp == 1)
	{
		if ((int)(floor(10 * map.x) + floor(10 * map.y)) % 2)
			*color = CHECK_COLOR;
		else
			*color = inter->obj->color;
	}
	else if (temp == 2)
		*color = my_mlx_pixel_get(obj->texture.img,
				map.x * obj->texture.width, map.y * obj->texture.height);
	else
		*color = inter->obj->color;
	if (inter->obj->map >= 4)
		normal_perturbation(&obj->bump, normal, &map, 10);
}

void	get_sp_map(t_vect point, t_sp *sp, t_vect *map)
{
	t_vect		p;

	p = vec_sub(point, sp->center);
	map->x = atan2(p.y, p.x);
	map->x /= (2.0 * PI);
	map->y = acos(p.z / sp->radius);
	map->y /= PI;
}

void	get_pl_map(t_vect point, t_pl *pl, t_vect *map)
{
	t_vect	p;

	p = vec_sub(point, pl->point);
	map->x = dot(pl->base.h_normal, p);
	map->y = -dot(pl->base.v_normal, p);
}

void	get_disk_map(t_vect point, t_obj *obj, t_type mode, t_vect *map)
{
	if (mode == DISK)
		return (get_co_disk_map(point, (t_co *)obj, map));
	else
		return (get_cy_disk_map(point, (t_cy *)obj, mode, map));
}
