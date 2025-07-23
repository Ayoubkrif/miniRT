/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:29:57 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/23 12:32:20 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	rgb_to_height(int color, float height)
{
	float	ret_val;

	ret_val = (color >> 16) & 0xFF;
	ret_val += (color >> 8) & 0xFF;
	ret_val += color & 0xFF;
	return (height * (ret_val) / 765.0f);
}

float	average(float x1, float x2)
{
	return ((x1 - x2) * 0.5);
}

void	edge_secure(t_bump *bump, int x, int y, int h[4])
{
	if (x > 0)
		h[0] = x - 1;
	else
		h[0] = x;
	if (x < bump->width - 1)
		h[1] = x + 1;
	else
		h[1] = x;
	if (y > 0)
		h[2] = y - 1;
	else
		h[2] = y;
	if (y < bump->height - 1)
		h[3] = y + 1;
	else
		h[3] = y;
}

void	normal_perturbation(t_vect *normal, float h[4])
{
	t_base	base;
	t_vect	bump_normal;
	t_vect	new_normal;

	bump_normal = (t_vect){-average(h[1], h[0]), -average(h[3], h[2]), 1};
	normalize_to(&bump_normal);
	set_base(&base, *normal);
	new_normal.x = bump_normal.x * base.h_normal.x
		+ bump_normal.y * base.v_normal.x
		+ bump_normal.z * normal->x;
	new_normal.y = bump_normal.x * base.h_normal.y
		+ bump_normal.y * base.v_normal.y
		+ bump_normal.z * normal->y;
	new_normal.z = bump_normal.x * base.h_normal.z
		+ bump_normal.y * base.v_normal.z
		+ bump_normal.z * normal->z;
	normalize_to(&new_normal);
	*normal = new_normal;
}

void	bump_normal(t_bump *bump, t_vect *normal, t_vect *map, float height)
{
	float	hf[4];
	int		h[4];
	int		x;
	int		y;

	x = (int)(map->x * (bump->width - 1));
	y = (int)(map->y * (bump->height - 1));
	edge_secure(bump, x, y, h);
	hf[0] = rgb_to_height(my_mlx_pixel_get(bump->img, h[0], y), height);
	hf[1] = rgb_to_height(my_mlx_pixel_get(bump->img, h[1], y), height);
	hf[2] = rgb_to_height(my_mlx_pixel_get(bump->img, x, h[2]), height);
	hf[3] = rgb_to_height(my_mlx_pixel_get(bump->img, x, h[3]), height);
	normal_perturbation(normal, hf);
}
