/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 14:16:48 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

static void	translate_sp(int keycode, t_sp *sp)
{
	if (keycode == XK_w)
		sp->center = vec_add(sp->center, (t_vect){1, 0, 0});
	if (keycode == XK_s)
		sp->center = vec_sub(sp->center, (t_vect){1, 0, 0});
	if (keycode == XK_a)
		sp->center = vec_add(sp->center, (t_vect){0, 1, 0});
	if (keycode == XK_d)
		sp->center = vec_sub(sp->center, (t_vect){0, 1, 0});
	if (keycode == XK_space)
		sp->center = vec_add(sp->center, (t_vect){0, 0, 1});
	if (keycode == XK_Shift_L)
		sp->center = vec_sub(sp->center, (t_vect){0, 0, 1});
}

static void	increase_radius(int keycode, t_sp *sp)
{
	if (keycode == XK_KP_Add)
	{
		sp->diameter += 0.5;
	}
	if (keycode == XK_KP_Subtract)
	{
		sp->diameter -= 0.5;
	}
}

void	modify_sp(int keycode, t_sp *sp)
{
	translate_sp(keycode, sp);
	increase_radius(keycode, sp);
	set_sp(sp);
}

