/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_co.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/14 14:54:43 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

static void	translate_co(int keycode, t_co *co)
{
	if (keycode == XK_w)
		co->apex = vec_add(co->apex, (t_vect){1, 0, 0});
	if (keycode == XK_s)
		co->apex = vec_sub(co->apex, (t_vect){1, 0, 0});
	if (keycode == XK_a)
		co->apex = vec_add(co->apex, (t_vect){0, 1, 0});
	if (keycode == XK_d)
		co->apex = vec_sub(co->apex, (t_vect){0, 1, 0});
	if (keycode == XK_space)
		co->apex = vec_add(co->apex, (t_vect){0, 0, 1});
	if (keycode == XK_Shift_L)
		co->apex = vec_sub(co->apex, (t_vect){0, 0, 1});
}

static void	increase_radius(int keycode, t_co *co)
{
	if (keycode == XK_KP_Add)
	{
		co->diameter += 0.5;
	}
	if (keycode == XK_KP_Subtract)
	{
		co->diameter -= 0.5;
	}
}

void	modify_co(int keycode, t_co *co)
{
	increase_radius(keycode, co);
	translate_co(keycode, co);
	set_co(co);
}
