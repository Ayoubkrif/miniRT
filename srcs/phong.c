/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/03 10:15:40 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "vect.h"

typedef struct s_phong
{
	t_vect	ray_cam_obj_n;
	t_inter	inter_cam;
	t_rgb	solid_color;
	t_rgb	lights_color;
	t_vect	ray_light_obj_n;
	t_inter	inter_light;
	t_vect	point_cam;
	t_vect	point_light;
	t_vect	normal_n;
	double	dot_normal_light;
	double	dot_normal_cam;
	t_rgb	diffuse;
	t_vect	h;
	t_rgb	specular;
}	t_phong;

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular, t_light light)
{
	*light_color = color_add(*light_color, color_mul(color_add(diffuse, specular), (t_rgb){light.color.brightness, light.color.brightness, light.color.brightness, 1}));
}

t_rgb	diffuse_color(t_phong phong, t_light light)
{
	return ((t_rgb){light.color.r, light.color.g, light.color.b,
		KD * fabs(phong.dot_normal_light)});
}

t_rgb	specular_color(t_phong phong, t_light light)
{
	return ((t_rgb){light.color.r, light.color.g, light.color.b,
		KS * fabs(pow(dot(phong.normal_n, phong.h), ALPHA_S))});
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_phong	phong;
	int	i;

	i = 0;
	phong.ray_cam_obj_n = normalize(ray_from_camera_to_objects(rt->camera, x, y));
	phong.inter_cam = add_inter(rt, phong.ray_cam_obj_n, rt->camera.position);
	if (!phong.inter_cam.obj)
		return ((t_rgb){0, 0, 0, 0});
	phong.solid_color = phong.inter_cam.color;
	phong.lights_color = rt->ambiant.color;
	phong.point_cam = get_point(rt->camera.position, phong.ray_cam_obj_n, phong.inter_cam.t);
	phong.normal_n = normal_vect(phong.inter_cam, phong.point_cam);
	phong.dot_normal_cam = -dot(phong.ray_cam_obj_n, phong.normal_n);
	while (i < rt->nb_light)
	{
		phong.diffuse = (t_rgb){0, 0, 0, 0};
		phong.specular = (t_rgb){0, 0, 0, 0};
		phong.ray_light_obj_n = normalize(vec_sub(phong.point_cam, rt->light[i].position));
		phong.inter_light = add_inter(rt, phong.ray_light_obj_n, rt->light[i].position);
		phong.point_light = get_point(rt->light[i].position, phong.ray_light_obj_n, phong.inter_light.t);
		if (vect_eq(phong.point_cam, phong.point_light))
		{
			phong.dot_normal_light = dot(vec_mul(phong.ray_light_obj_n, -1), phong.normal_n);
			if ((phong.dot_normal_light < 0 && phong.dot_normal_cam < 0)
				|| (phong.dot_normal_light > 0 && phong.dot_normal_cam > 0))
			{
				phong.diffuse = diffuse_color(phong, rt->light[i]);
				phong.h = normalize(vec_add(phong.ray_light_obj_n, phong.ray_cam_obj_n));
				phong.specular = specular_color(phong, rt->light[i]);
			}
		}
		add_lights(&phong.lights_color, phong.diffuse, phong.specular, rt->light[i]);
		i++;
	}
	phong.lights_color = color_mul(phong.lights_color, (t_rgb){255, 255, 255, 1});
	return (color_mul(phong.solid_color, phong.lights_color));
}
