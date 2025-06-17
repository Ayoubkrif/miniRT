/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/17 18:45:19 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "mlx.h"

t_inter	add_inter(t_rt *rt, t_vect ray)
{
	int		i;
	t_inter	inter;

	i = 0;
	inter = (t_inter){-1, (t_rgb){0, 0, 0, 1}, NULL};
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(rt, ray, (t_sp *)rt->object[i], &inter);
		else if (*rt->object[i] == CYLINDER)
			inter_cylinder(rt, ray, (t_cy *)rt->object[i], &inter);
		else if (*rt->object[i] == PLANE)
			inter_plane(rt, ray, (t_pl *)rt->object[i], &inter);
		i++;
	}
	return (inter);
}

t_rgb	shaker_ambiant_solid(t_rt *rt, t_rgb color, t_rgb diffuse)
{
	(void)rt;
	return ((t_rgb)
		{
			color.r * /* ((rt->ambiant.color.r * rt->ambiant.color.brightness) + */(diffuse.brightness * diffuse.r),
			color.g * /* ((rt->ambiant.color.g * rt->ambiant.color.brightness) + */(diffuse.brightness * diffuse.g),
			color.b * /* ((rt->ambiant.color.b * rt->ambiant.color.brightness) + */(diffuse.brightness * diffuse.b),
			1
		});
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray_cam_obj;
	t_cam	*cam;
	t_inter	inter_ray_obj;

	cam = &rt->camera;
	ray_cam_obj = vec_add(vec_mul(cam->screen.pix_x, x),
			vec_mul(cam->screen.pix_y, y));
	ray_cam_obj = vec_add(cam->screen.center, ray_cam_obj);
	ray_cam_obj = vec_sub(ray_cam_obj, cam->position);
	inter_ray_obj = add_inter(rt, ray_cam_obj);

	t_vect	inter_obj_cam;
	t_vect	ray_light_obj;
	t_inter	diffuse;
	t_vect	inter_obj_light;

	inter_obj_cam = get_point_d(rt->camera.position, ray_cam_obj, inter_ray_obj.t);
	ray_light_obj = vec_sub(inter_obj_cam, rt->light.position);
	diffuse = add_inter(rt, ray_light_obj);
	inter_obj_light = get_point_d(rt->light.position, ray_light_obj, diffuse.t);
	if (vect_eq(inter_obj_cam, inter_obj_light))
		diffuse.color = rt->light.color;
	else
		diffuse.color = (t_rgb){0, 0, 0, 0};
	return (shaker_ambiant_solid(rt, inter_ray_obj.color, diffuse.color));
}

#include <stdio.h>

void	throwing_rays_through_the_wide_universe(t_rt *rt)
{
	int	i;
	int	j;

	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\ncolor    :%f%f%f\n",
		rt->light.position.x, rt->light.position.y, rt->light.position.z, rt->light.color.brightness
		, rt->light.color.r * 255, rt->light.color.g * 255, rt->light.color.b * 255);
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
/*color = shaker_ambiant_solid(rt, is_it_touching(rt, (double)i, -(double)j));*/
/*my_mlx_pixel_put(rt, i, j, color);*/
/*int		shaker_ambiant_solid(t_rt *rt, t_rgb color)*/
/*{*/
/*	int		final_color;*/
/*	t_rgb	light_color;*/
/**/
/*	final_color = (((int)(color.r * 255 * rt->ambiant) << 16))*/
/*		| (((int)(color.g * 255) << 8))*/
/*		| ((int)(color.b * 255));*/
/*}*/
