/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/14 17:13:08 by aykrifa          ###   ########.fr       */
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
	}
	if (keycode == XK_KP_Subtract)
	{
		cy->diameter -= 0.5;
	}
}

static void	increase_height(int keycyde, t_cy *cy)
{
	if (keycyde == XK_KP_Multiply)
	{
		cy->height += 0.5;
	}
	if (keycyde == XK_KP_Divide)
	{
		cy->height -= 0.5;
	}
}

static void	rotate_cy(int keycode, t_cy *cy)
{
	t_vect	temp;

	temp = cy->axis_n;
	if (keycode == XK_Left)
	{
		cy->axis_n = vec_sub(vec_mul(cy->axis_n, COS),
				vec_mul(cy->base.h_normal, SIN));
		cy->base.h_normal = vec_add(vec_mul(cy->base.h_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Right)
	{
		cy->axis_n = vec_add(vec_mul(cy->axis_n, COS),
				vec_mul(cy->base.h_normal, SIN));
		cy->base.h_normal = vec_sub(vec_mul(cy->base.h_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Up)
	{
		cy->axis_n = vec_add(vec_mul(cy->axis_n, COS),
				vec_mul(cy->base.v_normal, SIN));
		cy->base.v_normal = vec_sub(vec_mul(cy->base.v_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Down)
	{
		cy->axis_n = vec_sub(vec_mul(cy->axis_n, COS),
				vec_mul(cy->base.v_normal, SIN));
		cy->base.v_normal = vec_add(vec_mul(cy->base.v_normal, COS),
				vec_mul(temp, SIN));
	}
}

void	modify_cy(int keycode, t_cy *cy)
{
	translate_cy(keycode, cy);
	rotate_cy(keycode, cy);
	increase_radius(keycode, cy);
	increase_height(keycode, cy);
	/*set_base(&cy->base, cy->axis_n);*/
	set_cy(cy);
}
