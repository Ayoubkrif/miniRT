/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:29:57 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/22 13:48:05 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include <math.h>

float	rgb_to_height(int color, float height)
{
	int	r = (color >> 16) & 0xFF;
	int	g = (color >> 8) & 0xFF;
	int	b = color & 0xFF;
	return (height * (r + g + b) / 765.0f);
}

void	bump_normal(t_bump *bump, t_vect *normal, t_vect *map, float height)
{
	t_base	base;
	t_vect	new_normal;
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
	set_base(&base, *normal); // *normal est la normale originale
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
