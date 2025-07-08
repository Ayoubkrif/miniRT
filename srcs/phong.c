/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/08 11:56:10 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "miniRT.h"
#include "define.h"
#include "vect.h"
#include <stdio.h>

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
}	t_phong;

#define N_REFLECTION 5

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

t_rgb	specular_color(t_phong phong, t_light light, t_vect h)
{
	float	ks;

	ks = KS * fabs(pow(dot(phong.normal_n, h), ALPHA_S));
	return (
		color_mul((t_rgb){ks, ks, ks},
		(t_rgb){light.color.r, light.color.g, light.color.b}
		));
}

t_rgb	blin_phong(t_rt *rt, t_vect ray, t_phong phong)
{
	int		i;
	t_rgb	diffuse;
	t_rgb	specular;
	t_vect	h;

	i = 0;
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
				diffuse = diffuse_color(phong, rt->light[i]);
				h = normalize(vec_add(phong.light_obj_n, ray));
				specular = specular_color(phong, rt->light[i], h);
				add_lights(&phong.lights_color, diffuse, specular, rt->light[i]);
			}
		}
		i++;
	}
	return (phong.lights_color);
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision)
{
	t_phong	phong;
	t_rgb	lights;
	t_rgb	reflected;

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
	phong.solid_color = phong.inter_ray.color;
	int	r = 1;
	int	l = 1;
	if (phong.inter_ray.reflexion > EPSILON && precision)
		reflected = cast_ray_from(rt, phong.reflected, vec_add(phong.point_ray, vec_mul(phong.reflected, EPSILON)), precision - 1);
	else
		reflected = (t_rgb){0, 0, 0}, r = 0;
	if (!(phong.inter_ray.reflexion > 1 - EPSILON && precision))
		lights = blin_phong(rt, ray, phong);
	else
		lights = (t_rgb){0, 0, 0}, l = 0;
	lights = color_add(rt->ambient.color, lights);
	if (l && r)
		return (color_add(color_k(color_mul(phong.solid_color, lights), 1 - phong.inter_ray.reflexion), color_k(reflected, phong.inter_ray.reflexion)));
	else if (!r && l)
		return (color_mul(phong.solid_color, lights));
	else if (r && !l)
		return (reflected);
	else
		return((t_rgb){0, 0, 0});
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	return (cast_ray_from(rt, ray_from_camera_to_objects(rt->camera, x, y), rt->camera.position, N_REFLECTION));
}
