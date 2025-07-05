/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/05 13:55:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "vect.h"

typedef struct s_phong
{
	t_inter	inter_ray;
	t_rgb	solid_color;
	t_rgb	lights_color;
	t_vect	light_obj_n;
	t_inter	inter_light;
	t_vect	point_ray;
	t_vect	point_light;
	t_vect	normal_n;
	t_vect	reflected;
	double	dot_normal_light;
	double	dot_normal_ray;
	t_rgb	diffuse;
	t_vect	h;
	t_rgb	specular;
}	t_phong;

#define N_REFLECTION 15

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular, t_light light)
{
	(void)light;
	*light_color = color_add(*light_color, color_add(diffuse, specular));
}

//(t_rgb){}
t_rgb	diffuse_color(t_phong phong, t_light light)
{
	float	kd;

	kd = KD * fabs(phong.dot_normal_light);
	return (
		color_mul((t_rgb){kd, kd, kd},
		(t_rgb){light.color.r, light.color.g, light.color.b}
		));
}

t_rgb	specular_color(t_phong phong, t_light light)
{
	float	ks;

	ks = KS * fabs(pow(dot(phong.normal_n, phong.h), ALPHA_S));
	return (
		color_mul((t_rgb){ks, ks, ks},
		(t_rgb){light.color.r, light.color.g, light.color.b}
		));
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision)
{
	t_phong	phong;
	int	i;

	i = 0;
	ray = normalize(ray);
	phong.inter_ray = add_inter(rt, ray, from);
	if (!phong.inter_ray.obj)
		return ((t_rgb){0, 0, 0});
	phong.point_ray = get_point(from, ray, phong.inter_ray.t);
	phong.normal_n = normal_vect(phong.inter_ray, phong.point_ray);
	phong.dot_normal_ray = -dot(ray, phong.normal_n);
	if (phong.dot_normal_ray < 0)
	{
		phong.normal_n = vec_mul(phong.normal_n, -1);
		phong.dot_normal_ray *= -1;
	}
	phong.reflected = vec_sub(vec_mul(phong.normal_n, 2 * phong.dot_normal_ray), vec_mul(ray, -1));
	if (phong.inter_ray.mode == SPHERE && precision)
		return (cast_ray_from(rt, phong.reflected, vec_add(phong.point_ray, vec_mul(phong.reflected, EPSILON)), precision - 1));
	else
	{
		phong.solid_color = phong.inter_ray.color;
		phong.lights_color = rt->ambient.color;
		while (i < rt->nb_light)
		{
			phong.light_obj_n = normalize(vec_sub(phong.point_ray, rt->light[i].position));
			phong.inter_light = add_inter(rt, phong.light_obj_n, rt->light[i].position);
			phong.point_light = get_point(rt->light[i].position, phong.light_obj_n, phong.inter_light.t);
			if (vect_eq(phong.point_ray, phong.point_light))
			{
				phong.dot_normal_light = dot(vec_mul(phong.light_obj_n, -1), phong.normal_n);
				if (phong.dot_normal_light > 0)
				{
					phong.diffuse = diffuse_color(phong, rt->light[i]);
					phong.h = normalize(vec_add(phong.light_obj_n, ray));
					phong.specular = specular_color(phong, rt->light[i]);
					add_lights(&phong.lights_color, phong.diffuse, phong.specular, rt->light[i]);
				}
			}
			i++;
		}
	}
	return (color_mul(phong.solid_color, phong.lights_color));
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	return (cast_ray_from(rt, ray_from_camera_to_objects(rt->camera, x, y), rt->camera.position, N_REFLECTION));
}
