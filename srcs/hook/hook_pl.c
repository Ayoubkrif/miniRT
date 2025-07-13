/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 13:21:30 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

static void	translate_pl(int keycode, t_pl *pl)
{
	if (keycode == XK_w)
		pl->point = vec_add(pl->point, (t_vect){1, 0, 0});
	if (keycode == XK_s)
		pl->point = vec_sub(pl->point, (t_vect){1, 0, 0});
	if (keycode == XK_a)
		pl->point = vec_add(pl->point, (t_vect){0, 1, 0});
	if (keycode == XK_d)
		pl->point = vec_sub(pl->point, (t_vect){0, 1, 0});
	if (keycode == XK_space)
		pl->point = vec_add(pl->point, (t_vect){0, 0, 1});
	if (keycode == XK_Shift_L)
		pl->point = vec_sub(pl->point, (t_vect){0, 0, 1});
	set_pl(pl);
}

void	modify_pl(int keycode, t_pl *pl)
{
	translate_pl(keycode, pl);
	set_pl(pl);
}
