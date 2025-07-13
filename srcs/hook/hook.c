/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 15:55:17 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

void	modify_sp(int keycode, t_sp *sp);
void	modify_pl(int keycode, t_pl *pl);
void	modify_cy(int keycode, t_cy *cy);
void	modify_co(int keycode, t_co *co);
void	modify_cam(int keycode, t_cam *cam);

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == XK_Escape)
		exit_minirt(rt);
	else if (keycode == XK_c)
		rt->menu = 0;
	else if (keycode == XK_n)
	{
		if (rt->menu == rt->nb_object)
			rt->menu = 0;
		else
			rt->menu++;
	}
	else
	{
		if (rt->menu == 0)
			modify_cam(keycode, &rt->camera);
		else
		{
			if (*rt->object[rt->menu - 1] == PLANE)
				modify_pl(keycode, (t_pl *)rt->object[rt->menu - 1]);
			if (*rt->object[rt->menu - 1] == SPHERE)
				modify_sp(keycode, (t_sp *)rt->object[rt->menu - 1]);
			if (*rt->object[rt->menu - 1] == CYLINDER)
				modify_cy(keycode, (t_cy *)rt->object[rt->menu - 1]);
			if (*rt->object[rt->menu - 1] == CONE)
				modify_co(keycode, (t_co *)rt->object[rt->menu - 1]);
		}
		window_cast(rt);
	}
	return (0);
}
