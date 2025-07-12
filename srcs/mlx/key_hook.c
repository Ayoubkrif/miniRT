/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/12 15:46:14 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

static void	rotate_cam(int keycode, t_cam *cam)
{
	t_vect	temp;

	temp = cam->direction_n;
	if (keycode == XK_Left)
	{
		cam->direction_n = vec_sub(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.h_normal, SIN));
		cam->base.h_normal = vec_add(vec_mul(cam->base.h_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Right)
	{
		cam->direction_n = vec_add(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.h_normal, SIN));
		cam->base.h_normal = vec_sub(vec_mul(cam->base.h_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Up)
	{
		cam->direction_n = vec_add(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.v_normal, SIN));
		cam->base.v_normal = vec_sub(vec_mul(cam->base.v_normal, COS),
				vec_mul(temp, SIN));
	}
	if (keycode == XK_Down)
	{
		cam->direction_n = vec_sub(vec_mul(cam->direction_n, COS),
				vec_mul(cam->base.v_normal, SIN));
		cam->base.v_normal = vec_add(vec_mul(cam->base.v_normal, COS),
				vec_mul(temp, SIN));
	}
}

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
	rotate_cam(keycode, cam);
	/*set_base(&cam->base, cam->direction_n);*/
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
	if (keycode == XK_KP_Add)
	{
		sp->diameter += 0.5;
		sp->radius += 0.25;
	}
	if (keycode == XK_KP_Subtract)
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
	set_pl(pl);
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
	cy->top = get_point_t(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot(cy->top, cy->axis_n);
	cy->bottom
		= get_point_t(cy->center, vec_mul(cy->axis_n, -1), cy->semi_height);
	cy->db = -dot(cy->bottom, cy->axis_n);
}

void	modify_co(int keycode, t_co *co)
{
	if (keycode == XK_w)
		co->center = vec_add(co->center, (t_vect){1, 0, 0});
	if (keycode == XK_s)
		co->center = vec_sub(co->center, (t_vect){1, 0, 0});
	if (keycode == XK_a)
		co->center = vec_add(co->center, (t_vect){0, 1, 0});
	if (keycode == XK_d)
		co->center = vec_sub(co->center, (t_vect){0, 1, 0});
	if (keycode == XK_space)
		co->center = vec_add(co->center, (t_vect){0, 0, 1});
	if (keycode == XK_Shift_L)
		co->center = vec_sub(co->center, (t_vect){0, 0, 1});
	if (keycode == XK_KP_Add)
	{
		co->diameter += 0.5;
		co->radius += 0.25;
	}
	if (keycode == XK_KP_Subtract)
	{
		co->diameter -= 0.5;
		co->radius -= 0.25;
	}
	co->gamma = p2(co->height) / (p2(co->radius) + p2(co->height));
	co->apex = get_point_t(co->center, op(co->axis_n), co->height);
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
			if (*rt->object[rt->menu - 1] == CONE)
				modify_co(keycode, (t_co *)rt->object[rt->menu - 1]);
		}
		throwing_rays_through_the_wide_universe(rt);
	}
	return (0);
}
