/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 15:49:21 by aykrifa          ###   ########.fr       */
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

static void	translate_cam(int keycode, t_cam *cam)
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
}

void	modify_cam(int keycode, t_cam *cam)
{
	translate_cam(keycode, cam);
	rotate_cam(keycode, cam);
	/*set_base(&cam->base, cam->direction_n);*/
	set_cam_base(cam);
}
