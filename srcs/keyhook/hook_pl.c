/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/14 09:24:02 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

static void	translate_pl(int keycode, t_pl *pl)
{
	if (keycode == XK_w)
		pl->point = vec_add(pl->point, pl->normal_n);
	if (keycode == XK_s)
		pl->point = vec_sub(pl->point, pl->normal_n);
	set_pl(pl);
}

void	modify_pl(int keycode, t_pl *pl)
{
	translate_pl(keycode, pl);
	set_pl(pl);
}
