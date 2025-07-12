/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:56:54 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/12 15:01:01 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vect	normal_cone(t_co *co, t_vect point)
{
	t_vect	cy_n;

	cy_n = normalize(vec_sub(point, vec_add(co->apex, vec_mul(co->axis_n, dot(co->axis_n, vec_sub(point, co->apex)) / dot(co->axis_n, co->axis_n)))));
	return (vec_add(vec_mul(cy_n, cos(co->theta)), vec_mul(co->axis_n, -sin(co->theta))));
}

static t_vect	normal_cylinder(t_cy *cy, t_vect point)
{
	return (normalize(
			vec_sub(point,
				vec_add(cy->center,
					vec_mul(cy->axis_n,
						dot(cy->axis_n,
							vec_sub(point, cy->center))
						/ dot(cy->axis_n, cy->axis_n))))));
}

t_vect	normal_vect(t_inter inter, t_vect point)
{
	if (inter.mode == SPHERE)
		return (normalize(
				vec_sub(((t_sp *)inter.obj)->center, point)));
	if (inter.mode == PLANE)
		return (((t_pl *)inter.obj)->normal_n);
	if (inter.mode == CYLINDER)
	{
		return (normal_cylinder((t_cy *)inter.obj, point));
	}
	if (inter.mode == CONE)
		return (normal_cone((t_co *)inter.obj, point));
	else
		return (((t_cy *)inter.obj)->axis_n);
}

t_vect	ray_from_camera_to_objects(t_cam cam, double x, double y)
{
	t_vect	ray_cam_obj;

	ray_cam_obj = vec_add(vec_mul(cam.screen.pix_x, x),
			vec_mul(cam.screen.pix_y, y));
	ray_cam_obj = vec_add(cam.screen.center, ray_cam_obj);
	ray_cam_obj = vec_sub(ray_cam_obj, cam.position);
	return (ray_cam_obj);
}
