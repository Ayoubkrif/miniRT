/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/02 12:57:37 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "vect.h"

typedef struct s_phong
{
	t_inter	inter_light;
	t_inter	inter_cam;
	t_vect	point_cam;
	t_vect	point_light;
	t_vect	normal_n;
	double	dot_normal_light;
	double	dot_normal_cam;
	t_rgb	diffuse;

	t_vect	ray_light_obj_n;
	t_vect	ray_cam_obj_n;
	t_vect	h;
	t_vect	reflect;
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
	return (color_mul(color_mul(solid_color, color_add(rt->ambiant.color, color_mul(color_add(diffuse, specular),
						(t_rgb){rt->light.color.brightness, rt->light.color.brightness, rt->light.color.brightness, 1}))),
					(t_rgb){255, 255, 255, 0}));
}

t_rgb	diffuse_color(t_rt *rt, t_phong phong)
{
	return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,
		KD * fabs(phong.dot_normal_light)});
}

t_rgb	specular_color(t_rt *rt, t_phong phong)
{
	(void)rt;
	return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,
		KS * fabs(pow(dot_prod(phong.normal_n, phong.h), ALPHA_S))});
	/*return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,*/
	/*	rt->light.color.brightness * fabs(pow(dot_prod(phong.reflect, phong.ray_cam_obj_n), 100))});*/
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_phong	phong;

	phong.ray_cam_obj_n = get_normalized_vec(ray_from_camera_to_objects(rt->camera, x, y));
	phong.inter_cam = add_inter(rt, phong.ray_cam_obj_n, rt->camera.position);

	phong.point_cam = get_point_d(rt->camera.position, phong.ray_cam_obj_n, phong.inter_cam.t);
	
	phong.ray_light_obj_n = get_normalized_vec(vec_sub(phong.point_cam, rt->light.position));

	phong.inter_light = add_inter(rt, phong.ray_light_obj_n, rt->light.position);
	phong.point_light = get_point_d(rt->light.position, phong.ray_light_obj_n, phong.inter_light.t);
	phong.diffuse = (t_rgb){0, 0, 0, 0};
	phong.specular = (t_rgb){0, 0, 0, 0};
	if (vect_eq(phong.point_cam, phong.point_light))
	{
		phong.normal_n = normal_vect(phong.inter_light, phong.point_cam);
		phong.dot_normal_light = dot_prod(vec_mul(phong.ray_light_obj_n, -1), phong.normal_n);
		phong.dot_normal_cam = dot_prod(vec_mul(phong.ray_cam_obj_n, -1), phong.normal_n);
		if ((phong.dot_normal_light < 0 && phong.dot_normal_cam < 0)
			|| ((phong.dot_normal_light > 0 && phong.dot_normal_cam > 0) && (vec_mul(phong.normal_n, -1), 1)))
		{
			phong.diffuse = diffuse_color(rt, phong);
			phong.h = get_normalized_vec(vec_add(phong.ray_light_obj_n, phong.ray_cam_obj_n));
			/*phong.reflect = get_normalized_vec(vec_sub(vec_mul(phong.normal_n, 2 * phong.dot_normal_light), phong.ray_light_obj_n));*/
			phong.specular = specular_color(rt, phong);
		}
	}
	return (shaker_ambiant_solid(rt, phong.inter_cam.color, phong.diffuse, phong.specular));
}
