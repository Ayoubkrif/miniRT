/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/01 19:05:21 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect.h"

typedef struct s_phong
{
	t_inter	inter_light;
	t_inter	inter_cam;
	t_vect	point_cam;
	t_vect	point_light;
	t_vect	normal_n;
	t_vect	h;
	double	dot_normal_light;
	double	dot_normal_cam;
	t_rgb	diffuse;
	t_rgb	specular;
}	t_phong;

t_vect	normal_cylinder(t_cy *cy, t_vect point)
{
	return (get_normalized_vec(
			vec_sub(point,
				vec_add(cy->center,
					vec_mul(cy->axis_n,
						dot_prod(cy->axis_n,
							vec_sub(point, cy->center)) / dot_prod(cy->axis_n, cy->axis_n))))));
}

t_vect	normal_vect(t_inter inter, t_vect point)
{
	if (inter.mode == SPHERE)
		return (get_normalized_vec(
				vec_sub(((t_sp *)inter.obj)->center, point)));
	if (inter.mode == PLANE)
		return (((t_pl *)inter.obj)->normal_n);
	if (inter.mode == CYLINDER)
	{
		return (normal_cylinder((t_cy *)inter.obj, point));
	}
	if (inter.mode == DISK_BOT)
		return (((t_cy *)inter.obj)->axis_n);
	else
		return (((t_cy *)inter.obj)->axis_n);
}

t_rgb	shaker_ambiant_solid(t_rt *rt, t_rgb solid_color, t_rgb diffuse, t_rgb specular)
{
	(void)specular;
	return (color_mul(solid_color, color_add(diffuse, rt->ambiant.color)));
}

t_rgb	diffuse_color(t_rt *rt, t_phong phong)
{
	return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,
		rt->light.color.brightness * fabs(phong.dot_normal_light)});
}

t_rgb	specular_color(t_rt *rt, t_phong phong)
{
	(void)rt;
	return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,
		rt->light.color.brightness * fabs(pow(dot_prod(phong.normal_n, phong.h), 100))});
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray_cam_obj;
	t_vect	ray_light_obj;
	t_phong	phong;

	ray_cam_obj = ray_from_camera_to_objects(rt->camera, x, y);
	phong.inter_cam = add_inter(rt, ray_cam_obj, rt->camera.position);
	phong.point_cam = get_point_d(rt->camera.position, ray_cam_obj, phong.inter_cam.t);
	ray_light_obj = vec_sub(phong.point_cam, rt->light.position);
	phong.inter_light = add_inter(rt, ray_light_obj, rt->light.position);
	phong.point_light = get_point_d(rt->light.position, ray_light_obj, phong.inter_light.t);
	phong.diffuse = (t_rgb){0, 0, 0, 0};
	phong.specular = (t_rgb){0, 0, 0, 0};
	if (vect_eq(phong.point_cam, phong.point_light))
	{
		phong.normal_n = normal_vect(phong.inter_light, phong.point_cam);
		phong.dot_normal_light = dot_prod(get_normalized_vec(
					vec_sub(rt->light.position, phong.point_cam)), phong.normal_n);
		phong.dot_normal_cam = dot_prod(vec_sub(rt->camera.position, phong.point_cam), phong.normal_n);
		if ((phong.dot_normal_light > 0 && phong.dot_normal_cam > 0)
			|| (phong.dot_normal_light < 0 && phong.dot_normal_cam < 0))
		{
			phong.diffuse = diffuse_color(rt, phong);
			phong.h = get_normalized_vec(vec_add(get_normalized_vec(ray_light_obj), get_normalized_vec(ray_cam_obj)));
			phong.specular = specular_color(rt, phong);
		}
	}
	return (shaker_ambiant_solid(rt, phong.inter_cam.color, phong.diffuse, phong.specular));
}
