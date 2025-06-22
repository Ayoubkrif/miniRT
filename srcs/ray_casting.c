/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/22 16:36:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

t_inter	add_inter(t_rt *rt, t_vect ray, t_vect	start)
{
	int		i;
	t_inter	inter;

	i = 0;
	inter = (t_inter){-1, (t_rgb){0, 0, 0, 1}, NULL, NONE};
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(ray, (t_sp *)rt->object[i], &inter, start);
		else if (*rt->object[i] == CYLINDER)
			inter_cylinder(ray, (t_cy *)rt->object[i], &inter, start);
		else if (*rt->object[i] == PLANE)
			inter_plane(ray, (t_pl *)rt->object[i], &inter, start);
		i++;
	}
	return (inter);
}

t_rgb	shaker_ambiant_solid(t_rt *rt, t_rgb color, t_rgb diffuse)
{	
	return (color_mul(color, color_add(diffuse, rt->ambiant.color)));
}

t_vect	normal_vect(t_inter inter, t_vect point)
{
	if (inter.mode == SPHERE)
		return (get_normalized_vec(
				vec_sub(((t_sp *)inter.obj)->center, point)));
	if (inter.mode == PLANE)
		return (((t_pl *)inter.obj)->normal_n);
	if (inter.mode == CYLINDER)
		return (get_normalized_vec(
				vec_sub(point, ((t_cy *)inter.obj)->center)));
	if (inter.mode == DISK_BOT)
		return (((t_cy *)inter.obj)->axis_n);
	else
		return (((t_cy *)inter.obj)->axis_n);
}

t_rgb	diffuse_color(t_rt *rt, t_inter inter, t_vect point)
{
	t_vect	normal_n;
	double	dot_n_light;
	double	dot_n_camera;

	normal_n = normal_vect(inter, point);
	dot_n_light = dot_prod(get_normalized_vec(
				vec_sub(rt->light.position, point)), normal_n);
	dot_n_camera = dot_prod(vec_sub(rt->camera.position, point), normal_n);
	if ((dot_n_light > 0 && dot_n_camera > 0)
		|| (dot_n_light < 0 && dot_n_camera < 0))
		return ((t_rgb){rt->light.color.r, rt->light.color.g, rt->light.color.b,
			rt->light.color.brightness * fabs(dot_n_light)});
	else
		return ((t_rgb){0, 0, 0, 0});
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

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray_cam_obj;
	t_inter	inter_obj_cam;
	t_vect	point_obj_cam;	
	t_vect	ray_light_obj;
	t_inter	diffuse;
	t_vect	inter_light_obj;

	ray_cam_obj = ray_from_camera_to_objects(rt->camera, x, y);
	inter_obj_cam = add_inter(rt, ray_cam_obj, rt->camera.position);
	point_obj_cam = get_point_d(rt->camera.position, ray_cam_obj, inter_obj_cam.t);
	ray_light_obj = vec_sub(point_obj_cam, rt->light.position);
	diffuse = add_inter(rt, ray_light_obj, rt->light.position);
	inter_light_obj = get_point_d(rt->light.position, ray_light_obj, diffuse.t);
	if (vect_eq(point_obj_cam, inter_light_obj))
		diffuse.color = diffuse_color(rt, diffuse, point_obj_cam);
	else
		diffuse.color = (t_rgb){0, 0, 0, 0};
	return (shaker_ambiant_solid(rt, inter_obj_cam.color, diffuse.color));
}

void	throwing_rays_through_the_wide_universe(t_rt *rt)
{
	int	i;
	int	j;

	i = -WIN_X / 2;
	while (i < WIN_X / 2)
	{
		j = -WIN_Y / 2;
		while (j < WIN_Y / 2)
		{
			put_a_pixel(rt, i + (WIN_X / 2), j + (WIN_Y / 2),
				is_it_touching(rt, (double)i, -(double)j));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(rt->mlx.disp, rt->mlx.win, rt->mlx.img, 0, 0);
}
