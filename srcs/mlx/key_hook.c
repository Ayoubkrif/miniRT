/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/01 08:33:15 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

void	modify_cam(int keycode, t_cam *cam)
{
	if (keycode == XK_w)
		cam->position = vec_add(cam->position, cam->direction_n);
	if (keycode == XK_s)
		cam->position = vec_sub(cam->position, cam->direction_n);
	if (keycode == XK_d)
		cam->position = vec_add(cam->position, cam->base.h_normal);
	if (keycode == XK_a)
		cam->position = vec_sub(cam->position, cam->base.h_normal);
	if (keycode == XK_space)
		cam->position = vec_add(cam->position, cam->base.v_normal);
	if (keycode == XK_Shift_L)
		cam->position = vec_sub(cam->position, cam->base.v_normal);
	if (keycode == XK_Left)
		cam->direction_n = vec_sub(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.h_normal, SIN));
	if (keycode == XK_Right)
		cam->direction_n = vec_add(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.h_normal, SIN));
	if (keycode == XK_Up)
		cam->direction_n = vec_add(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.v_normal, SIN));
	if (keycode == XK_Down)
		cam->direction_n = vec_sub(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.v_normal, SIN));
	set_cam_base(cam);
}

void	modify_sp(int keycode, t_sp *sp)
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
	if (keycode == XK_parenleft)
	{
		sp->diameter += 0.5;
		sp->radius += 0.25;
	}
	if (keycode == XK_parenright)
	{
		sp->diameter -= 0.5;
		sp->radius -= 0.25;
	}
}

void	modify_pl(int keycode, t_pl *pl)
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
	pl->d = -dot_prod(pl->point, pl->normal_n);
}

void	modify_cy(int keycode, t_cy *cy)
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
	cy->top = get_point(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot_prod(cy->top, cy->axis_n);
	cy->bottom
		= get_point(cy->center, vec_mul(cy->axis_n, -1), cy->semi_height);
	cy->db = -dot_prod(cy->bottom, cy->axis_n);
}

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
		}
		throwing_rays_through_the_wide_universe(rt);
	}
	return (0);
}
