/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 13:21:42 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

static void	translate_cy(int keycode, t_cy *cy)
{
	if (keycode == XK_w)
		cy->center = vec_add(cy->center, (t_vect){1, 0, 0});
	if (keycode == XK_s)
		cy->center = vec_sub(cy->center, (t_vect){1, 0, 0});
	if (keycode == XK_a)
		cy->center = vec_add(cy->center, (t_vect){0, 1, 0});
	if (keycode == XK_d)
		cy->center = vec_sub(cy->center, (t_vect){0, 1, 0});
	if (keycode == XK_space)
		cy->center = vec_add(cy->center, (t_vect){0, 0, 1});
	if (keycode == XK_Shift_L)
		cy->center = vec_sub(cy->center, (t_vect){0, 0, 1});
}

static void	increase_radius(int keycode, t_cy *cy)
{
	if (keycode == XK_KP_Add)
	{
		cy->diameter += 0.5;
		cy->radius += 0.25;
	}
	if (keycode == XK_KP_Subtract)
	{
		cy->diameter -= 0.5;
		cy->radius -= 0.25;
	}
}

void	modify_cy(int keycode, t_cy *cy)
{
	translate_cy(keycode, cy);
	increase_radius(keycode, cy);

	cy->top = get_point_t(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot(cy->top, cy->axis_n);
	cy->bottom
		= get_point_t(cy->center, vec_mul(cy->axis_n, -1), cy->semi_height);
	cy->db = -dot(cy->bottom, cy->axis_n);
}
