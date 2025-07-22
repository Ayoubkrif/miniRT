/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/22 10:30:33 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include <X11/keysym.h>

#define SIN	0.26
#define COS 0.97

void	modify_sp(int keycode, t_sp *sp);
void	modify_pl(int keycode, t_pl *pl);
void	modify_cy(int keycode, t_cy *cy);
void	modify_co(int keycode, t_co *co);
void	modify_cam(int keycode, t_cam *cam);

int	select_solid(int button, int x, int y, t_rt *rt)
{
	t_vect	ray;
	t_obj	*obj;
	int		i;

	if (button == 1)
	{
		if (x < WIN_X && x >= 0)
			x -= WIN_X / 2;
		else
			return (1);
		if (y < WIN_Y && y >= 0)
			y = -y + WIN_Y / 2;
		else
			return (1);
	}
	else
		return (1);
	ray = ray_from_camera_to_objects(rt->camera, x, y);
	obj = nearest_inter(rt, ray, rt->camera.position).obj;
	if (!obj)
		return (1);
	i = 0;
	while (rt->object[i] != (t_type *)obj)
		i++;
	rt->menu = i + 1;
	mlx_put_image_to_window(rt->mlx.disp, rt->mlx.win, rt->mlx.img, 0, 0);
	put_string(rt);
	return (0);
}

static void	set_offset(int keycode, t_obj *obj)
{
	if (keycode == XK_KP_Left)
		obj->u_offset -= 0.083;
	if (keycode == XK_KP_Right)
		obj->u_offset += 0.083;
	if (keycode == XK_KP_Up)
		obj->v_offset += 0.083;
	if (keycode == XK_KP_Down)
		obj->v_offset -= 0.083;
}

static void	modify_obj(int keycode, t_type *obj)
{
	set_offset(keycode, (t_obj *)obj);
	if (*obj == PLANE)
		modify_pl(keycode, (t_pl *)obj);
	if (*obj == SPHERE)
		modify_sp(keycode, (t_sp *)obj);
	if (*obj == CYLINDER)
		modify_cy(keycode, (t_cy *)obj);
	if (*obj == CONE)
		modify_co(keycode, (t_co *)obj);
}

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == XK_Escape)
		exit_minirt(rt, 0);
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
			modify_obj(keycode, rt->object[rt->menu - 1]);
		window_cast(rt);
	}
	return (0);
}
