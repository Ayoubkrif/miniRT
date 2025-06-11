/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 11:04:43 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"

void	alloc_camera_scene(t_type *obj[], t_type *to_dup[])
{
	int	i;

	i = 0;
	while (obj[i])
	{
		if (*obj[i] == PLANE)
			to_dup[i] = malloc(sizeof(t_plane));
		if (*obj[i] == SPHERE)
			to_dup[i] = malloc(sizeof(t_sphere));
		if (*obj[i] == CYLINDER)
			to_dup[i] = malloc(sizeof(t_cylinder));
		i++;
	}
}

void	set_cam_base(t_rt *rt)
{
	rt->c_base.h_dir = vec_prod(rt->camera.direction, vec(0, 0, 1));
	rt->c_base.v_dir = vec_prod(rt->camera.direction, rt->c_base.h_dir);
	rt->c_base.start = get_point(rt->camera.position, rt->camera.direction, 1);
	rt->c_base.pixel_x = get_point(vec(0, 0, 0), rt->c_base.h_dir, tan(to_rad(45)) / 960);
	rt->c_base.pixel_y = get_point(vec(0, 0, 0), rt->c_base.v_dir, vec_norm(rt->c_base.pixel_x));
}

void	set_cam_obj(t_rt *rt)
{
	static int	dup = 0;

	if (!dup)
	{
		alloc_camera_scene(rt->object, rt->cam_obj);
		dup++;
	}
	set_cam_base(rt);
}
