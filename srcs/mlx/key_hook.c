/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/14 22:20:04 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "math_utils.h"
#include <X11/keysym.h>

void	modify_cam(int keycode, t_rt *rt)
{
	int	param;

	// if (keycode == XK_w)
	// 	rt->camera.position = vec_add(rt->camera.position, rt->camera.direction);
	// if (keycode == XK_w)
	// 	rt->camera.position = vec_sub(rt->camera.position, rt->camera.direction);
	if (keycode == XK_equal)
		keycode = 1;
	else
		keycode = -1;
	param = rt->menu.value % 7;
	if (param == 0)
		rt->camera.position.x += keycode;
	else if (param == 1)
		rt->camera.position.y += keycode;
	else if (param == 2)
		rt->camera.position.z += keycode;
	else if (param == 3)
		rt->camera.direction.x += 0.1 * keycode;
	else if (param == 4)
		rt->camera.direction.y += 0.1 * keycode;
	else if (param == 5)
		rt->camera.direction.z += 0.1 * keycode;
	else
		rt->camera.fov += keycode;
	set_cam_obj(rt);
}

void	modify_sp(int keycode, t_rt *rt, t_sp *sp)
{
	int	param;

	if (keycode == XK_equal)
		keycode = 1;
	else
		keycode = -1;
	param = rt->menu.value % 4;
	if (param == 0)
		sp->center.x += keycode;
	else if (param == 1)
		sp->center.y += keycode;
	else if (param == 2)
		sp->center.z += keycode;
	else
		sp->diameter += (keycode * 0.5);
}

void	modify_pl(int keycode, t_rt *rt, t_pl *pl)
{
	int	param;

	if (keycode == XK_equal)
		keycode = 1;
	else
		keycode = -1;
	param = rt->menu.value % 6;
	if (param == 0)
		pl->point.x += keycode;
	else if (param == 1)
		pl->point.y += keycode;
	else if (param == 2)
		pl->point.z += keycode;
	else if (param == 3)
		pl->normal.x += keycode * 0.1;
	else if (param == 4)
		pl->normal.y += keycode * 0.1;
	else
		pl->normal.z += keycode * 0.1;
	pl->d = -dot_prod(pl->point, pl->normal);
}

void	modify_cy(int keycode, t_rt *rt, t_cy *cy)
{
	int	param;

	if (keycode == XK_equal)
		keycode = 1;
	else
		keycode = -1;
	param = rt->menu.value % 8;
	if (param == 0)
		cy->center.x += keycode;
	else if (param == 1)
		cy->center.y += keycode;
	else if (param == 2)
		cy->center.z += keycode;
	else if (param == 3)
		cy->axis.x += keycode * 0.1;
	else if (param == 4)
		cy->axis.y += keycode * 0.1;
	else if (param == 5)
		cy->axis.z += keycode * 0.1;
	else if (param == 6)
		cy->diameter += keycode;
	else
		cy->height += keycode;
	cy->top = get_point(cy->center, cy->axis, cy->height / 2);
	cy->dt = -dot_prod(cy->top, cy->axis);
	cy->bottom = get_point(cy->center, vec_mul(cy->axis, -1), cy->height / 2);
	cy->db = -dot_prod(cy->bottom, cy->axis);
}

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == XK_Escape)
		exit_minirt(rt);
	else if (keycode == XK_n)
	{
		rt->menu.value = 0;
		if (rt->menu.obj == rt->nb_object)
			rt->menu.obj = 0;
		else
			rt->menu.obj++;
	}
	else if (keycode == XK_m)
		rt->menu.value++;
	else if (keycode == XK_space)
		throwing_rays_through_the_wide_universe(rt);
	else if (rt->menu.obj == 0)
		modify_cam(keycode, rt);
	else
	{
		if (*rt->object[rt->menu.obj - 1] == PLANE)
			modify_pl(keycode, rt, (t_pl *)rt->object[rt->menu.obj - 1]);
		if (*rt->object[rt->menu.obj - 1] == SPHERE)
			modify_sp(keycode, rt, (t_sp *)rt->object[rt->menu.obj - 1]);
		if (*rt->object[rt->menu.obj - 1] == CYLINDER)
			modify_cy(keycode, rt, (t_cy *)rt->object[rt->menu.obj - 1]);
	}
	print_solids(rt);
	return (0);
}
