/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/15 15:39:18 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "math_utils.h"
#include <X11/keysym.h>

#define SIN	0.013707355
#define COS	0.999990509

void	modify_cam(int keycode, t_cam *cam)
{

	if (keycode == XK_w)
		cam->position = vec_add(cam->position, cam->direction);
	if (keycode == XK_s)
		cam->position = vec_sub(cam->position, cam->direction);
	if (keycode == XK_a)
		cam->position = vec_add(cam->position, cam->base.h_normal);
	if (keycode == XK_d)
		cam->position = vec_sub(cam->position, cam->base.h_normal);
	if (keycode == XK_space)
		cam->position = vec_add(cam->position, cam->base.v_normal);
	if (keycode == XK_Shift_L)
		cam->position = vec_sub(cam->position, cam->base.v_normal);
	if (keycode == XK_Left)
		cam->direction = vec_sub(vec_mul(cam->direction, COS), vec_mul(cam->base.h_normal, SIN));
	if (keycode == XK_Right)
		cam->direction = vec_add(vec_mul(cam->direction, COS), vec_mul(cam->base.h_normal, SIN));
	if (keycode == XK_Up)
		cam->direction = vec_add(vec_mul(cam->direction, COS), vec_mul(cam->base.v_normal, SIN));
	if (keycode == XK_Down)
		cam->direction = vec_sub(vec_mul(cam->direction, COS), vec_mul(cam->base.v_normal, SIN));
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
	pl->d = -dot_prod(pl->point, pl->normal);
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
	else
	{
		if (rt->menu.obj == 0)
			modify_cam(keycode, &rt->camera);
		else
		{
			if (*rt->object[rt->menu.obj - 1] == PLANE)
				modify_pl(keycode, (t_pl *)rt->object[rt->menu.obj - 1]);
			if (*rt->object[rt->menu.obj - 1] == SPHERE)
				modify_sp(keycode, (t_sp *)rt->object[rt->menu.obj - 1]);
			if (*rt->object[rt->menu.obj - 1] == CYLINDER)
				modify_cy(keycode, (t_cy *)rt->object[rt->menu.obj - 1]);
		}
		throwing_rays_through_the_wide_universe(rt);
	}
	/*print_solids(rt);*/
	return (0);
}
